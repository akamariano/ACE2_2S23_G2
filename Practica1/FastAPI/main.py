from fastapi import FastAPI
from routes.sensors import routes_sensor


app = FastAPI()

app.include_router(routes_sensor, prefix="/sensors")
