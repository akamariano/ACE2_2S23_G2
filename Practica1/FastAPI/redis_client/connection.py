from redis import Redis
from redis.exceptions import ConnectionError
from os import getenv


try:
    redis_client = Redis(
        host='',
        port=38131,
        password=''
    )

    print("Connected to Redis")
except ConnectionError as e:
    print("Connection to Redis failed")
    print(e)