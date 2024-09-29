/**
 * @name Sumedh Sandeep Lele
 * BITS_ID: 2024HT01137
 *
 * @details This is the source code for the ESP826 NodeMCU used for the Mini Project to send the data
 * to the server hosted locally both for HTTP as well as MQTT.
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>

// Wi-Fi credentials
const char *ssid = "enter wifi ssid";
const char *password = "enter you wifi password";

// MQTT broker details (your laptop's IP where the Mosquitto broker is running)
const char *mqtt_server = "192.168.29.3";

// HTTP server details (your laptop's IP where the Flask server is running)
const char *serverName = "http://192.168.29.3:5000/data";

// Set the MQTT client
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Buffer for UART data
String receivedString = "";

// Function to connect to Wi-Fi
void setup_wifi()
{
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

// Function to reconnect to MQTT Broker
void reconnect_mqtt()
{
	while (!mqttClient.connected())
	{
		Serial.print("Attempting MQTT connection...");
		if (mqttClient.connect("ESP8266Client"))
		{
			Serial.println("connected");
		}
		else
		{
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
			delay(5000);
		}
	}
}

// Send data via MQTT
void send_mqtt(const char *topic, const char *payload)
{
	if (!mqttClient.connected())
	{
		reconnect_mqtt();
	}
	mqttClient.publish(topic, payload);
	Serial.println("MQTT message sent: ");
	Serial.println(payload);
}

// Send data via HTTP POST
void send_http(const char *data)
{
	if (WiFi.status() == WL_CONNECTED)
	{
		HTTPClient http;
		// http.begin(serverName);
		http.begin(espClient, serverName);
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		String postData = "data=" + String(data);
		// Add Content-Length header (length of the data you're sending)
    	// int contentLength = postData.length();  // Calculate the length of the data
		// http.addHeader("Content-Length", String(contentLength));
		Serial.println(postData);
		int httpResponseCode = http.POST(postData);

		if (httpResponseCode > 0)
		{
			String response = http.getString();
			Serial.print("HTTP Response code: ");
			Serial.println(httpResponseCode);
			Serial.println("HTTP Response: " + response);
		}
		else
		{
			Serial.print("Error in sending POST request: ");
			Serial.println(httpResponseCode);
		}
		http.end();
	}
	else
	{
		Serial.println("WiFi Disconnected");
	}
}

// Function to parse the received string and handle data transmission
void parse_and_send(String input)
{
	input.trim(); // Remove any leading or trailing whitespace
	if (input.startsWith("$") && input.endsWith("#"))
	{
		// Remove the '$' at the start and '#' at the end
		input = input.substring(1, input.length() - 1);

		// Split the string at the first comma to get the method and data
		int firstCommaIndex = input.indexOf(',');
		if (firstCommaIndex != -1)
		{
			String method = input.substring(0, firstCommaIndex); // Either "http" or "mqtt"
			String data = input.substring(firstCommaIndex + 1);	 // The actual data

			// Send data based on the method
			if (method == "http")
			{
				Serial.println("Sending via HTTP...");
				send_http(data.c_str());
			}
			else if (method == "mqtt")
			{
				Serial.println("Sending via MQTT...");
				send_mqtt("test/topic", data.c_str());
			}
			else
			{
				Serial.println("Invalid method");
			}
		}
		else
		{
			Serial.println("Invalid input format. No comma found.");
		}
	}
	else
	{
		Serial.println("Invalid input format. Expected $ and # as delimiters.");
	}
}

// Setup function
void setup()
{
	Serial.begin(115200);
	setup_wifi();
	mqttClient.setServer(mqtt_server, 1883);
}

// Loop function
void loop()
{
	if (Serial.available())
	{
		char inChar = (char)Serial.read();
		receivedString += inChar;

		// Check for end-of-frame character '#'
		if (inChar == '#')
		{
			Serial.print("Received string: ");
			Serial.println(receivedString);

			// Parse and process the string
			parse_and_send(receivedString);

			// Clear the buffer for the next input
			receivedString = "";
		}
	}
	delay(10); // Small delay for stability
}
