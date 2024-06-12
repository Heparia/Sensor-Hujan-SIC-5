from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/sensorhujan', methods=['POST'])
def post_func():
    if request.method == "POST":
        data = request.get_json() 
        persentase = data.get('persentase')   
        response = {
            'status': 'success',
            'message': 'Data berhasil dikirim',
            'persentase': persentase,
        }
        return jsonify(response), 201 

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)