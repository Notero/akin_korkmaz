# US Visa Appointment Scheduler (Turkey)

An automation tool designed to monitor and manage US visa appointment scheduling on official portals for users in Turkey.

## Project Inventory

- **`USvize.py`**: The main automation script utilizing Selenium to interact with the appointment scheduling website.
- **`test.py`**: A diagnostic script for verifying Selenium configurations and WebDriver connectivity.
- **`chromedriver`**: The specific version-matched ChromeDriver used for browser automation.
- **`.venv/`**: A isolated Python virtual environment containing the project's dependencies (e.g., Selenium).

## Features
- **Automated Monitoring**: Periodically checks for newly available appointment slots.
- **Configuration Management**: Users can specify criteria for their preferred appointment dates.
- **Browser Automation**: Mimics user behavior to navigate the appointment dashboard safely.

## How-To
- **Prerequisites**: Python 3.x and Chrome browser installed.
- **Execution**: Activate the virtual environment and run `USvize.py`.

---
*Created as a functional utility to simplify a complex scheduling process.*
