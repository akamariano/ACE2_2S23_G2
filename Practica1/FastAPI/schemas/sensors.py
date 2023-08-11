from pydantic import BaseModel, Field
from uuid import uuid4
from datetime import datetime

def generate_uuid():
    return str(uuid4())

def generate_date():
    return str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))

class Sensor(BaseModel):
    id: str = Field(default_factory=generate_uuid)
    sensor_type: int
    value: float
    timestamp: str = Field(default_factory=generate_date)