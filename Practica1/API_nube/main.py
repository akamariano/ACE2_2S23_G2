from fastapi import FastAPI
from rutas.ambiente import ruta_ambiente

app = FastAPI()

app.include_router(ruta_ambiente, prefix="/ambiente")