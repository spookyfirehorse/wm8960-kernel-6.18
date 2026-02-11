# rpi 4 kernel 6.18

```bash
cat << 'EOF' > install_wm8960_rpi4_6.18.sh
#!/bin/bash
# WM8960 Installer für RPi 4 - Optimiert für Kernel 6.18
# Nutzt das integrierte snd-soc-wm8960 Modul

echo "--- Installiere WM8960 für RPi 4 (Kernel 6.18) ---"

# 1. System-Tools sicherstellen
sudo apt update
sudo apt install -y device-tree-compiler i2c-tools

# 2. Das High-Precision Overlay für Kernel 6.18 erstellen
cat << 'DTS' > wm8960-rpi4.dts
/dts-v1/;
/plugin/;

/ {
    compatible = "brcm,bcm2711";

    /* I2S am BCM2711 aktivieren */
    fragment@0 {
        target = <&i2s>;
        __overlay__ {
            status = "okay";
        };
    };

    /* I2C1 für den WM8960 Codec */
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
                /* Kernel 6.18 benötigt oft explizite Clock-Referenzen */
                clocks = <&clocks 38>; // BCM2835_CLK_GP0
                clock-names = "mclk";
                AVDD-supply = <&vdd_3v3_reg>;
                DVDD-supply = <&vdd_3v3_reg>;
            };
        };
    };

    /* Soundkarten-Definition (Simple-Audio-Card) */
    fragment@2 {
        target-path = "/";
        __overlay__ {
            wm8960_card {
                compatible = "simple-audio-card";
                simple-audio-card,name = "WM8960-Audio";
                simple-audio-card,format = "i2s";
                
                /* RPi 4 ist Master */
                simple-audio-card,bitclock-master = <&cpudai>;
                simple-audio-card,frame-master = <&cpudai>;

                cpudai: simple-audio-card,cpu {
                    sound-dai = <&i2s>;
                    dai-tdm-slot-num = <2>;
                    dai-tdm-slot-width = <32>;
                };

                simple-audio-card,codec {
                    sound-dai = <&wm8960>;
                };
            };
        };
    };
};
DTS

# 3. Kompilieren (DTC ist hier die sicherste Wahl)
dtc -@ -I dts -O dtb -o wm8960-rpi4.dtbo wm8960-rpi4.dts

# 4. Installation in den neuen Boot-Pfad
# Kernel 6.18 nutzt oft /boot/firmware/ (Debian 12/13 Standard)
DEST="/boot/firmware/overlays"
[ ! -d "$DEST" ] && DEST="/boot/overlays"

sudo cp wm8960-rpi4.dtbo "$DEST/"

# 5. Config.txt Bereinigung und Aktivierung
CONFIG="/boot/firmware/config.txt"
[ ! -f "$CONFIG" ] && CONFIG="/boot/config.txt"

sudo sed -i '/wm8960-rpi4/d' "$CONFIG"
echo "dtoverlay=wm8960-rpi4" | sudo tee -a "$CONFIG"
echo "dtparam=i2c_arm=on" | sudo tee -a "$CONFIG"

echo "--- Installation abgeschlossen! ---"
echo "Ein Neustart wird dringend empfohlen: sudo reboot"
EOF

chmod +x install_wm8960_rpi4_6.18.sh
./install_wm8960_rpi4_6.18.sh
```


# rpi 5

```bash
cat << 'EOF' > install_wm8960_rpi5.sh
#!/bin/bash
# WM8960 Installer für RPi 5 - Kernel 6.12
# Nutzt den RP1-I/O-Controller für I2S und I2C

echo "--- Starte WM8960 Installation für RPi 5 ---"

# 1. Tools installieren
sudo apt update
sudo apt install -y device-tree-compiler i2c-tools

# 2. Das RPi 5 spezifische Overlay (DTS)
cat << 'DTS' > wm8960-rpi5.dts
/dts-v1/;
/plugin/;

/ {
    /* Kompatibilität für RPi 5 (BCM2712) */
    compatible = "brcm,bcm2712";

    /* I2S am RP1-Chip aktivieren */
    fragment@0 {
        target = <&i2s_rp1>;
        __overlay__ {
            status = "okay";
        };
    };

    /* I2C am RP1-Chip aktivieren */
    fragment@1 {
        target = <&i2c1_rp1>;
        __overlay__ {
            #address-cells = <1>;
            #size-cells = <0>;
            status = "okay";

            wm8960: wm8960@1a {
                compatible = "wlf,wm8960";
                reg = <0x1a>;
                #sound-dai-cells = <0>;
                /* RPi 5 braucht oft explizite Power-Definitionen */
                AVDD-supply = <&vdd_3v3_reg>;
                DVDD-supply = <&vdd_3v3_reg>;
            };
        };
    };

    /* Die Soundkarte verbinden */
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
                    sound-dai = <&i2s_rp1>;
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
dtc -@ -I dts -O dtb -o wm8960-rpi5.dtbo wm8960-rpi5.dts

# 4. Installation
sudo cp wm8960-rpi5.dtbo /boot/firmware/overlays/ 2>/dev/null || sudo cp wm8960-rpi5.dtbo /boot/overlays/

# 5. Config.txt anpassen (RPi 5 Pfad beachten)
CONFIG_PATH="/boot/firmware/config.txt"
[ ! -f $CONFIG_PATH ] && CONFIG_PATH="/boot/config.txt"

sudo sed -i '/dtoverlay=wm8960-rpi5/d' $CONFIG_PATH
sudo sed -i '/dtparam=i2c_arm=on/d' $CONFIG_PATH
echo "dtparam=i2c_arm=on" | sudo tee -a $CONFIG_PATH
echo "dtoverlay=wm8960-rpi5" | sudo tee -a $CONFIG_PATH

echo "--- Fertig für RPi 5! ---"
echo "System wird in 5 Sekunden neu gestartet..."
sleep 5
sudo reboot
EOF

chmod +x install_wm8960_rpi5.sh
./install_wm8960_rpi5.sh
```



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


