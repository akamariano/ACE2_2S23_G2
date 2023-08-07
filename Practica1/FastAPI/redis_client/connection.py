from redis import Redis
from redis.exceptions import ConnectionError
from os import getenv

# Insert Redis credentials here
try:
    redis_client = Redis(
        host='',
        port=0,
        password=''
    )

    print("Connected to Redis")
except ConnectionError as e:
    print("Connection to Redis failed")
    print(e)