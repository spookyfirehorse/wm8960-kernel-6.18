# rpi 4

```bash
cat << 'EOF' > install_wm8960_rpi4.sh
#!/bin/bash
# WM8960 Installer für RPi 4 - Kernel 6.12
# Nutzt das integrierte Kernel-Modul via Device Tree Overlay

echo "--- Starte WM8960 Installation für RPi 4 ---"

# 1. Tools installieren
sudo apt update
sudo apt install - -y device-tree-compiler i2c-tools

# 2. Das Overlay-File (DTS) speziell für RPi 4 / BCM2711
cat << 'DTS' > wm8960-rpi4.dts
/dts-v1/;
/plugin/;

/ {
    /* Anpassung für RPi 4 */
    compatible = "brcm,bcm2711";

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

# 3. Kompilieren
dtc -@ -I dts -O dtb -o wm8960-rpi4.dtbo wm8960-rpi4.dts

# 4. Installation
sudo cp wm8960-rpi4.dtbo /boot/overlays/

# 5. Config.txt (Sed löscht alte Versuche, tee fügt neu hinzu)
sudo sed -i '/dtoverlay=wm8960-rpi4/d' /boot/config.txt
sudo sed -i '/dtparam=i2c_arm=on/d' /boot/config.txt
echo "dtparam=i2c_arm=on" | sudo tee -a /boot/config.txt
echo "dtoverlay=wm8960-rpi4" | sudo tee -a /boot/config.txt

echo "--- Fertig für RPi 4! Bitte rebooten ---"
EOF

chmod +x install_wm8960_rpi4.sh
./install_wm8960_rpi4.sh
```

# rpi 3

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
# rpi zero2w


```bash

cat << 'EOF' > install_wm8960_zero2w.sh
#!/bin/bash
# WM8960 Installer für RPi Zero 2 W - Kernel 6.12
# Basiert auf dem BCM2837 (RPi 3 Architektur)

echo "--- Starte WM8960 Installation für RPi Zero 2 W ---"

# 1. Benötigte Tools
sudo apt update
sudo apt install -y device-tree-compiler i2c-tools

# 2. Das Overlay-File (DTS)
# Der Zero 2 W ist kompatibel mit brcm,bcm2835 (Legacy-Support) 
# oder spezifisch brcm,bcm2710.
cat << 'DTS' > wm8960-zero2w.dts
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

# 3. Kompilieren
dtc -@ -I dts -O dtb -o wm8960-zero2w.dtbo wm8960-zero2w.dts

# 4. Installation
sudo cp wm8960-zero2w.dtbo /boot/overlays/

# 5. Config.txt anpassen
sudo sed -i '/dtoverlay=wm8960-zero2w/d' /boot/config.txt
sudo sed -i '/dtparam=i2c_arm=on/d' /boot/config.txt
echo "dtparam=i2c_arm=on" | sudo tee -a /boot/config.txt
echo "dtoverlay=wm8960-zero2w" | sudo tee -a /boot/config.txt

echo "--- Fertig für Zero 2 W! Rebooten mit: sudo reboot ---"
EOF

chmod +x install_wm8960_zero2w.sh
./install_wm8960_zero2w.sh
```


