from flask import Flask, request, render_template

app = Flask(__name__)

# Store data received via HTTP and MQTT
received_data = {"mqtt": "", "http": ""}

@app.route('/')
def index():
    return render_template('index.html', mqtt_data=received_data['mqtt'], http_data=received_data['http'])

@app.route('/data', methods=['POST'])
def receive_data():
    data = request.form.get('data', '')
    received_data['http'] = data
    return "Data received via HTTP", 200

def update_mqtt_data(data):
    received_data['mqtt'] = data

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
