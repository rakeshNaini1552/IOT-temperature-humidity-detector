# IOT-temperature-humidity-detector

Here are step-by-step instructions for a naive user to run the provided code:

### Running the Flask Server (`server.py`):

1. Make sure you have Python installed on your computer. If not, download and install it from the [official Python website](https://www.python.org/downloads/).

2. Open a text editor (like Notepad on Windows or TextEdit on Mac) and paste the provided Flask server code (`server.py`) into a new file.

3. Save the file with the name `server.py` in a convenient location on your computer.

4. Open a terminal or command prompt on your computer.

5. Navigate to the directory where you saved `server.py` using the `cd` command. For example:
   ```
   cd path/to/directory
   ```

6. Run the Flask server by entering the following command:
   ```
   python server.py
   ```

7. You should see some output indicating that the server is running. By default, the server will be accessible at `http://localhost:5000` in your web browser.

### Uploading and Running the Arduino Code:

1. Open the Arduino IDE on your computer.

2. Copy the provided Arduino code into a new sketch in the Arduino IDE.

3. Connect your ESP32 board to your computer using a USB cable.

4. Select the correct board and port in the Arduino IDE by going to `Tools` > `Board` and selecting your ESP32 board and the appropriate port.

5. Upload the sketch to your ESP32 board by clicking the "Upload" button in the Arduino IDE.

6. Open the Serial Monitor in the Arduino IDE by clicking the magnifying glass icon in the upper-right corner or navigating to `Tools` > `Serial Monitor`. You should see the temperature and humidity readings being printed in the Serial Monitor.

### Viewing the Data:

1. Open a web browser on your computer.

2. Enter the address `http://localhost:5000` in the address bar and press Enter. This will open the web interface for the Flask server, where you can see the temperature and humidity data being displayed.

3. The web page will automatically refresh every 5 seconds to display the latest data from the ESP32.

That's it! You have successfully set up and run the provided code to monitor temperature and humidity data from an ESP32 using a Flask server.
