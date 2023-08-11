from redis import Redis
from redis.exceptions import ConnectionError
from os import getenv

# Insert Redis credentials here
try:
    redis_client = Redis(
        host='us1-lasting-loon-38131.upstash.io',
        port=38131,
        password='f64f01dbf4584352a59673822e3d5eb3'
    
    )

    print("Connected to Redis")
except ConnectionError as e:
    print("Connection to Redis failed")
    print(e)