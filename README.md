```bash
cat << 'EOF' > install_wm8960.sh
#!/bin/bash
# WM8960 Installer für RPi 3 - Kernel 6.12 Fix
# Nutzt das integrierte Kernel-Modul via Device Tree Overlay

echo "--- Starte WM8960 Installation für RPi 3 (Kernel 6.12) ---"

# 1. Benötigtes Tool installieren (DTC braucht keine Kernel-Header!)
sudo apt update
sudo apt install -y device-tree-compiler i2c-tools

# 2. Das Overlay-File (DTS) erstellen
cat << 'DTS' > wm8960-rpi3.dts
/dts-v1/;
/plugin/;

/ {
    compatible = "brcm,bcm2835";

    fragment@0 {
        target = <&i2s>;
        __overlay__ {
            status = "okay";
        };
    };

    fragment@1 {
        target = <&i2c1>;
        __overlay__ {
            #address-cells = <1>;
            #size-cells = <0>;
            status = "okay";

            wm8960: wm8960@1a {
                compatible = "wlf,wm8960";
                reg = <0x1a>;
                #sound-dai-cells = <0>;
            };
        };
    };

    fragment@2 {
        target-path = "/";
        __overlay__ {
            wm8960_card {
                compatible = "simple-audio-card";
                simple-audio-card,name = "WM8960-Audio";
                simple-audio-card,format = "i2s";
                simple-audio-card,bitclock-master = <&cpudai>;
                simple-audio-card,frame-master = <&cpudai>;

                cpudai: simple-audio-card,cpu {
                    sound-dai = <&i2s>;
                };

                simple-audio-card,codec {
                    sound-dai = <&wm8960>;
                };
            };
        };
    };
};
DTS

# 3. Kompilieren des Overlays
echo "Kompiliere Device Tree Overlay..."
dtc -@ -I dts -O dtb -o wm8960-rpi3.dtbo wm8960-rpi3.dts

# 4. Installation
echo "Installiere Overlay in /boot/overlays/..."
sudo cp wm8960-rpi3.dtbo /boot/overlays/

# 5. Config.txt anpassen (verhindert Doppeleinträge)
echo "Aktiviere I2C und Overlay in /boot/config.txt..."
sudo sed -i '/dtoverlay=wm8960-rpi3/d' /boot/config.txt
sudo sed -i '/dtparam=i2c_arm=on/d' /boot/config.txt
echo "dtparam=i2c_arm=on" | sudo tee -a /boot/config.txt
echo "dtoverlay=wm8960-rpi3" | sudo tee -a /boot/config.txt

echo "--- Fertig! Bitte starte das System neu mit: sudo reboot ---"
EOF

# Script ausführbar machen und starten
chmod +x install_wm8960.sh
./install_wm8960.sh
```




# WM8960 Audio HAT

The drivers of [WM8960 Audio HAT] for Raspberry Pi.

http://www.waveshare.net/shop/WM8960-Audio-HAT.htm

http://www.waveshare.com/wm8960-audio-hat.htm

keyestudio 2 mic may others

https://www.amazon.de/dp/B07H3T8SQY?ref=ppx_yo2ov_dt_b_fed_asin_title


### Install wm8960-soundcard + seeed-2mic-voicecard 6.12 kernel 


```bash
git clone https://github.com/waveshare/WM8960-Audio-HAT
cd WM8960-Audio-HAT
sudo ./install.sh 
sudo reboot
```

### Install wm8960-soundcard + seeed-2mic-voicecard kernel 6.18

# without kernel headers

```bash
git clone https://github.com/spookyfirehorse/seeed-2mic-voicecard-wm8960-soundcard-kernel6.18.git
cd seeed-2mic-voicecard-wm8960-soundcard-kernel6.18/
sudo chmod +x  meine-install-ohne-kernel.sh
sudo ./ meine-install-ohne-kernel.sh 
```
# with kernel headers
```bash
git clone https://github.com/spookyfirehorse/seeed-2mic-voicecard-wm8960-soundcard-kernel6.18.git
cd seeed-2mic-voicecard-wm8960-soundcard-kernel6.18/
sudo chmod +x  meine-install.sh
sudo ./ meine-install-ohne-kernel.sh 
```



```bash
sudo reboot
```
#or

```bash
make
sudo make install
```

While the upstream wm8960 codec is not currently supported by current Pi kernel builds, upstream wm8960 has some bugs, we had fixed it. we must it build manually.

Check that the sound card name matches the source code wm8960-soundcard.

```bash
pi@raspberrypi:~ $ aplay -l
**** List of PLAYBACK Hardware Devices ****
card 0: ALSA [bcm2835 ALSA], device 0: bcm2835 ALSA [bcm2835 ALSA]
  Subdevices: 7/7
  Subdevice #0: subdevice #0
  Subdevice #1: subdevice #1
  Subdevice #2: subdevice #2
  Subdevice #3: subdevice #3
  Subdevice #4: subdevice #4
  Subdevice #5: subdevice #5
  Subdevice #6: subdevice #6
card 0: ALSA [bcm2835 ALSA], device 1: bcm2835 ALSA [bcm2835 IEC958/HDMI]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 1: wm8960soundcard [wm8960-soundcard], device 0: bcm2835-i2s-wm8960-hifi wm8960-hifi-0 []
  Subdevices: 1/1
  Subdevice #0: subdevice #0
pi@raspberrypi:~ $ arecord -l
**** List of CAPTURE Hardware Devices ****
card 1: wm8960soundcard [wm8960-soundcard], device 0: bcm2835-i2s-wm8960-hifi wm8960-hifi-0 []
  Subdevices: 1/1
  Subdevice #0: subdevice #0

```
If you want to change the alsa settings, You can use `sudo alsactl --file=/etc/wm8960-soundcard/wm8960_asound.state  store` to save it.


### Usage:
```bash
#It will capture sound an playback on hw:1
arecord -f cd -Dhw:1 | aplay -Dhw:1
```

```bash
#capture sound 
#arecord -d 10 -r 16000 -c 1 -t wav -f S16_LE test.wav
arecord -D hw:1,0 -f S32_LE -r 16000 -c 2 test.wav
```

```bash
#play sound file test.wav
aplay -D hw:1,0 test.wav
```

### uninstall wm8960-soundcard
If you want to upgrade the driver , you need uninstall the driver first.

```bash
pi@raspberrypi:~/WM8960-Audio-HAT $ sudo ./uninstall.sh 
...

------------------------------------------------------
Please reboot your raspberry pi to apply all settings
Thank you!
------------------------------------------------------
```

Enjoy !
