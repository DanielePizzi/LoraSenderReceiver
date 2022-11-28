# LoraSenderReceiver

* Node tracker tracker is a **LoRa SX1262**, with a **GPS AIR530 module**
* gateway,is a **ESP32 board**, with **LoRa SX1276** and **WIFI Module**


# Lora and Lorawan

it is important to make a distinction between Lora and LoRawan. LoRa is a technology based on chirp spread spectrum variation (CSS) with Forward Error Correction (FEC). The entire bandwidth is used to transmit a signal, effectively making it resistant to channel noise and resistant to fading, multipathing and Doppler effect, even at low powers. Unlike LoRaWan it is a MAC (Media Access control) protocol, designed to guarantee low-power devices to be able to communicate with applied applications via LPWAN (LoRaWan binds between the second and third level of the OSI model).

## Lora

As mentioned earlier, Lora is the physical layer or modulation used to create long range communication, and LoRa is based on the modulation of the chirp spectrum. The Chirp Spread Spectrum was already widely used in military and space, thanks to the fact that the communication system was able to cover large distances and to be able to resist interference, in this area LoRa is the first low cost for commercial use. As previously mentioned, its advantage is related to the fact that it has incredible long-range capabilities, in fact a single gateway or base station has the ability to cover even entire cities on a basis of hundreds of square kilometers. The range is greatly influenced by the surrounding environment and obstacles, however LoRa has a much higher link budget than currently standardized communication technologies.

## LoRaWAN

LoraWAN defines the communication protocol and system architecture at the network level, while LoRa enables its long-range communication link. Network protocol and architecture have the most impact on a node's battery life capability, quality of service, security, and availability of services from the network. Below is a diagram of the different layers of LoraWAN


## Pathloss by distance
refers to the loss or attenuation that a propagating electromagnetic signal (or wave) encounters along its path from transmitter to receiver. As a result of path loss, the power level of the received signal is several orders below the transmitted power level. The received power level depends on factors such as transmit power, antenna gains, operating frequency, and transmitter-receiver separation distance. Like any other gain or attenuation, path loss is also expressed in decibels (dB). We can relate received power level and path loss, but first let's know the expression for path loss.
![alt text](https://github.com/DanielePizzi/LoraSenderReceiver/blob/main/Data/pathloss%20by%20distance.png)
## RSSI by distance
RSSI (Received Signal Strength Indicator): Measures the amount of strength present in a radio signal. It is an approximate value for the strength of the signal received at an antenna. Measuring the signal strength at the receiving antenna is one way to determine the quality of a communications link. As a distant transmitter is brought closer to a receiver, the strength of the signal transmitted to the receiving antenna increases. Similarly, if a transmitter is moved away from it, the signal strength at the receiving antenna decreases. RSSI is measured in dBm. A larger negative value (in dBm) indicates a weaker signal. Therefore, -50dBm is better than -60dBm.
![alt text](https://github.com/DanielePizzi/LoraSenderReceiver/blob/main/Data/rssi%20by%20distance.png)
## PFE by distance
(packet Frequency error): Returns the frequency error of the received packet in Hz. Frequency error is the frequency offset between the center frequency of the receiver and that of an incoming LoRa signal.
![alt text](https://github.com/DanielePizzi/LoraSenderReceiver/blob/main/Data/pfe%20by%20distance.png)
## SNR by distance
SNR(Signal to Noise Ratio): In terms of definition, SNR or signal to noise ratio is the ratio of the desired information or power of a signal to the unwanted signal or power of the background noise. Also, the SNR is a measurement parameter used in science and engineering that compares the desired signal level to the background noise level. In other words, SNR is the ratio of signal power to noise power and its unit of expression is typically decibels (dB). Also, a ratio greater than 0 dB or greater than 1:1 indicates more signal than noise.
![alt text](https://github.com/DanielePizzi/LoraSenderReceiver/blob/main/Data/snr%20by%20distance.png)
