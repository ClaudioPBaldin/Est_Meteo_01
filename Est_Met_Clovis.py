import sys
import os
import serial
import BlynkLib
import time
from time import sleep, localtime, strftime

arduino = serial.Serial('/dev/ttyUSB0',9600)
blynk = BlynkLib.Blynk('gyUNW6wiQm73CFVZ58215OPI6YjAELqt')

while True:

    comparador = arduino.readline(1)
    dado = arduino.readline()
    dado2 = dado
    dado2 = float(dado)
    agora = strftime("%H:%M:%S", localtime())
    
        #   TEMPERATURA #
    if(comparador.decode("utf-8") == "T"):
        Temperatura = float(dado)
        blynk.virtual_write(1, Temperatura)        
        
        #   UMIDADE #
    if(comparador.decode("utf-8") == "U"):
        Umidade = float(dado)
        blynk.virtual_write(2, Umidade)
        
        #   PONTO DE ORVALHO    #
    if(comparador.decode("utf-8") == "O"):
        Orvalho = float(dado)
        blynk.virtual_write(4, Orvalho)

        #   VELOCIDADE DO VENTO #
    if(comparador.decode("utf-8") == "V"):
        Velocidade = float(dado)
        blynk.virtual_write(7, Velocidade)

        #   DIRECAO DO VENTO    #
    if(comparador.decode("utf-8") == "D"):
        if dado2 == 1:
            blynk.virtual_write(8, "Norte")
        if dado2 == 2:
            blynk.virtual_write(8, "Nordeste")
        if dado2 == 3:
            blynk.virtual_write(8, "Leste")
        if dado2 == 4:
            blynk.virtual_write(8, "Sudeste")
        if dado2 == 5:
            blynk.virtual_write(8, "Sul")
        if dado2 == 6:
            blynk.virtual_write(8, "Sudoeste")
        if dado2 == 7:
            blynk.virtual_write(8, "Oeste")
        if dado2 == 8:
            blynk.virtual_write(8, "Noroeste")            

        #   CHUVA   #
    if(comparador.decode("utf-8") == "C"):
        Chuva = float(dado)
        blynk.virtual_write(6, Chuva)

    if agora > "23:59:00" and agora < "23:59:10":
        os.system("sudo reboot")
