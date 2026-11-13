# Logic Analyser

This was built to analyse signal from different channels on my (Future) custom-made logic analyser. This will also consist of a companion desktop app to use with the logic analyser. 

>[!NOTE]
>If you want to read my full (ongoing) write up on this project to get more details and pictures, check out [my website](https://nosa.dev).

## Milestones

- [x] Capture a Single Channel 
- [x] Compare with known signal 
- [x] Store in Memory 
- [x] Measure Performance of capture (Currently doing)
- [ ] Support more channels
- [ ] Add capture controls
- [ ] Desktop App
- [ ] Generate Waveforms
- [ ] Decode UART
- [ ] Decode I²C 
- [ ] Decode SPI
- [ ] Build PCB

## End of human words. Below this line is ai.

### Setup: current ESP32 prototype

This setup runs the current single-channel firmware on a Freenove ESP32-WROVER. It detects changes on GPIO33 and sends the input level and elapsed time to a computer over USB serial.

The desktop application, protocol decoders, and custom PCB are planned milestones. They are not required to run this prototype.

### What you need

**Hardware**

- A Freenove ESP32-WROVER development board, as used in the FNK0047 kit.
- A USB cable that supports data and fits the board.
- A computer with an available USB port.
- A breadboard, jumper wires, and a normally open momentary pushbutton for the first input test.

The prototype stores its firmware in the ESP32's built-in flash. An SD card is not required for this test.

**Software**

- [Visual Studio Code](https://code.visualstudio.com/).
- The official [PlatformIO IDE extension](https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation). Its installation includes PlatformIO Core and the `pio` command.
- [Git](https://git-scm.com/downloads) if cloning the repository.
- Internet access for the first PlatformIO setup and build, which download the required platform and toolchain.

If Windows does not detect the board's serial port, follow [Freenove's USB driver instructions](https://docs.freenove.com/projects/fnk0047/en/latest/fnk0047/codes/C/Preface.html#ch340-importance) for the board.

### 1. Get the project

For a new checkout, run:

```powershell
git clone https://github.com/nosabecom/logicanalyser.git
cd logicanalyser
```

If you already have the project, open that checkout instead.

In VS Code, use **File > Open Folder** and select the folder containing `platformio.ini`. Allow PlatformIO to finish preparing the project.

The checked-in configuration selects:

```ini
[env:freenove_esp32_wrover]
platform = espressif32
board = freenove_esp32_wrover
framework = arduino
extra_scripts = post:scripts/esp32_intellisense.py
```

Keep the included `scripts/esp32_intellisense.py` file with the project; the configuration references it for editor include-path setup. See [PlatformIO's board documentation](https://docs.platformio.org/en/latest/boards/espressif32/freenove_esp32_wrover.html) for the board definition.

### 2. Wire the button input

Disconnect USB power before changing connections.

- Connect one switch contact to **GPIO33**, matching `inputPin` in `src/main.cpp`.
- Connect the other switch contact to **GND**.
- Use contacts that connect together when the button is pressed. On a typical four-leg tactile button, two legs may already be connected internally.

The firmware uses `INPUT_PULLUP`, so the ESP32's internal resistor holds the input HIGH when the button is open. No external pull-up resistor or power wire to the button is needed.

| Button state | GPIO33 level | Printed value |
| --- | --- | --- |
| Released | HIGH | `1` |
| Pressed | LOW | `0` |

> [!WARNING]
> The current input is connected directly to an ESP32 GPIO and is intended for 3.3 V logic. Do not apply 5 V signals directly. Use suitable level conversion or input circuitry before connecting a 5 V source.

For this first test, the button-to-GND circuit above is sufficient. When measuring another board later, its ground must be connected to the analyzer's ground as well.

### 3. Build the firmware

Open a **PlatformIO Core CLI** terminal from the PlatformIO tools in VS Code. Run the commands from the project folder containing `platformio.ini`.

```powershell
pio run
```

A successful build ends with `SUCCESS`. Building does not require the board to be connected.

### 4. Upload to the ESP32

Connect the board to the computer with the data-capable USB cable. Run the upload on the computer physically connected to the board.

Close any serial monitor using the port first, then run:

```powershell
pio run -t upload
```

This builds the firmware and uploads it to the ESP32. After a successful upload, the board normally resets and starts running it.

If PlatformIO needs an explicit port, list the connected devices:

```powershell
pio device list
```

Then supply the board's actual port. For example, if it is listed as `COM10`:

```powershell
pio run -t upload --upload-port COM10
```

### 5. Read the capture output

Open the serial monitor at the firmware's configured baud rate:

```powershell
pio device monitor -b 115200
```

If needed, select the same port explicitly:

```powershell
pio device monitor -p COM10 -b 115200
```

Replace `COM10` with the actual port. Press **Ctrl+C** to close the monitor before uploading again. See [PlatformIO's serial monitor documentation](https://docs.platformio.org/en/latest/core/userguide/device/cmd_monitor.html).

The current firmware prints one line when it observes an input change. For example:

```text
33,0,00:00:12:0345
```

The three comma-separated fields are:

| Field | Meaning |
| --- | --- |
| `33` | ESP32 GPIO number being monitored. |
| `0` | Observed input level: LOW is `0`, HIGH is `1`. |
| `00:00:12:0345` | Elapsed hours, minutes, seconds, and milliseconds within the current second. |

The last time component is currently padded to **four characters**, but its unit is still milliseconds: `0345` means 345 milliseconds. The clock measures elapsed time since startup, not the current time of day.

Press and release the button. Both actions change the signal and should produce records. The firmware does not continuously print an unchanged level.

### Current behavior and troubleshooting

- **Several records around one button action:** mechanical contact bounce can produce multiple real transitions. The prototype records observed edges rather than debouncing the signal.
- **Garbled terminal text:** ensure the monitor uses `115200`, matching `Serial.begin(115200)`, and that the latest firmware has been uploaded.
- **No input changes:** check the GPIO33 and GND connections and the switch's contact pairs. A released pull-up input staying at `1` is expected.
- **No serial port or upload failure:** check the USB data cable, board detection, driver, selected port, and whether another monitor has the port open.
- **`pio` is not recognized:** use the PlatformIO Core CLI terminal provided by the extension, or follow its shell-command setup instructions.
- **Timing limitations:** the current prototype polls the input, prints during capture, and reports millisecond timestamps. Maximum reliable signal speed and missed-event behavior have not yet been measured.

### Next validation step

Use a known, slow repeating 3.3 V signal and compare the observed input states and timestamps against the generated pattern. Buffered capture, finer timing, additional channels, and decoding are later milestones.
