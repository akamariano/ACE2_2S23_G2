from flask import Flask, jsonify, request, Response
from flask_pymongo import PyMongo
from bson import json_util
from bson.objectid import ObjectId

app = Flask(__name__)
app.config["MONGO_URI"] = "mongodb://localhost:27017/pythonmongodb"
mongo = PyMongo(app)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

# Create a new user (data)
@app.route('/create', methods=['POST'])
def create_data():
    # Receives Data
    username = request.json['username']
    password = request.json['password']

    if username and password:
        mongo.db.users.insert
        id = mongo.db.users.insert_one(
            {'username': username, 'password': password}
        )
        id = id.inserted_id
        response = {
            'id': str(id),
            'username': username,
            'password': password
        }
        return response
    else:
        return not_found()

# Obtain all users (data)
@app.route('/consult', methods=['GET'])
def get_data():
    users = mongo.db.users.find()
    response = json_util.dumps(users)

    return Response(response, mimetype='application/json')

# Obtain a user (data)
@app.route('/consult/<id>', methods=['GET'])
def get_user(id):
    # Find user by id (could be username, etc)
    user = mongo.db.users.find_one({'_id': ObjectId(id)})
    response = json_util.dumps(user)

    return Response(response, mimetype='application/json')

# Delete a user (data)
@app.route('/delete/<id>', methods=['DELETE'])
def delete_user(id):
    mongo.db.users.delete_one({'_id': ObjectId(id)})
    response = jsonify({'message': 'User ' + id + ' was deleted successfully'})
    response.status_code = 200

    return response

# Update a user (data)
@app.route('/update/<id>', methods=['PUT'])
def update_user():
    # Receives Data
    username = request.json['username']
    password = request.json['password']

    if username and password:
        mongo.db.users.update_one({'_id': ObjectId(id)}, {'$set': {
            'username': username,
            'password': password
        }})
        response = jsonify({'message': 'User ' + id + ' was updated successfully'})
        response.status_code = 200

        return response

@app.errorhandler(404)
def not_found(error = None):
    response = jsonify({
        'message': 'Resource not found ' + request.url,
        'status': 404
    })
    response.status_code = 404

    return response

if __name__ == '__main__':
    app.run( debug = True )
    