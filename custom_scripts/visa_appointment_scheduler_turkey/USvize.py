from datetime import datetime
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.select import Select
from selenium.common.exceptions import TimeoutException
import time

email = "" #input user email
password = "" #input user password

# Create a web driver
service = Service(absolute_path="/Users/akin/PycharmProjects/PythonProject1/chromedriver")
driver = webdriver.Chrome(service=service)

# Get the visa page for the US visa
driver.get("https://ais.usvisa-info.com/en-tr/niv/users/sign_in")

# Wait for the element with ID 'user_email' to appear
WebDriverWait(driver, 5).until(EC.presence_of_element_located((By.ID, "user_email")))

# Enter email
input_email = driver.find_element(By.ID, "user_email")
input_email.send_keys(email)

# Enter password
input_password = driver.find_element(By.ID, "user_password")
input_password.send_keys(password)

# Check the agreement box
I_agree = driver.find_element(By.CLASS_NAME, "icheckbox")
I_agree.click()

# Submit the form by pressing enter
input_password.send_keys(Keys.ENTER)

# Wait for the "Continue" button and click it
continue_button = WebDriverWait(driver, 5).until(EC.presence_of_element_located((By.LINK_TEXT, "Continue")))
continue_button.click()

#clicks on the header extends
reschedule_button = WebDriverWait(driver, 5).until(
    EC.element_to_be_clickable((By.LINK_TEXT, "Reschedule Appointment"))
)
reschedule_button.click()
#clicks on the green button
ireschedule_button = WebDriverWait(driver, 5).until(
        EC.element_to_be_clickable((By.XPATH, "//a[contains(text(), 'Reschedule Appointment')]"))
    )
ireschedule_button.click()


def last_date_update(inpdate):
    with open("/Users/akin/PycharmProjects/PythonProject1/USvize.txt", mode="w") as file:
        # Convert the date to a string in the format "YYYY-MM-DD"
        file.write(inpdate.strftime("%Y-%m-%d"))


# Function to read and retrieve the last reservation date from the file
def update_last_date():
    with open("/Users/akin/PycharmProjects/PythonProject1/USvize.txt", mode="r") as file:
        # Parse the date string and convert it back to a date object
        date_str = file.read().strip()  # Strip any whitespace/newlines
        return datetime.strptime(date_str, "%Y-%m-%d").date()

def refresh_and_wait(curr_driver, element_locator, timeout=30):
    """
    Refresh the page and wait until the specific element is found.
    If the element is not found within the timeout, refresh the page and try again.
    """
    # check every 10 min
    time.sleep(600)
    while True:
        try:

            # Refresh the page
            curr_driver.refresh()

            # Wait for the element to be present
            WebDriverWait(curr_driver, timeout).until(
                EC.presence_of_element_located(element_locator)
            )

            # If the element is found, break the loop
            print("Element found!")
            break

        except TimeoutException:
            # If the element is not found within the timeout, refresh again
            print("Timeout: Element not found. Refreshing the page...")

            continue

last_date = update_last_date()

while True:
    #ui-datepicker-div
    Date_picker = WebDriverWait(driver, 5).until(EC.element_to_be_clickable((By.ID, "appointments_consulate_appointment_date")))
    Date_picker.click()

    # Locate the datepicker container
    datepicker = driver.find_element(By.ID, "ui-datepicker-div")

    while True:
        # Get the current month and year
        month_year = datepicker.find_element(By.CLASS_NAME, "ui-datepicker-title").text
        print(month_year)
        # Get all available dates in the current month
        days = datepicker.find_elements(By.CSS_SELECTOR, "td span.ui-state-default")

        # Locate the datepicker calendar table
        table = driver.find_element(By.CLASS_NAME, "ui-datepicker-calendar")

        # Find all <td> elements inside the table
        all_td_elements = table.find_elements(By.TAG_NAME, "td")

        # Extract and print all classes for each <td>
        for td in all_td_elements:
            if td.get_attribute("class") == " undefined":

                    date_click = driver.find_element(By.LINK_TEXT, td.text)
                    date_click.click()

                    # Locate the <select> dropdown
                    dropdown = WebDriverWait(driver, 10).until(
                        EC.presence_of_element_located((By.ID, "appointments_consulate_appointment_time"))
                    )
                    dropdown.click()
                    time.sleep(5)

                    element_click = Select(dropdown)
                    element_click.select_by_index(1)

                    Reschedule_button = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, "appointments_submit")))
                    Reschedule_button.click()

                    Confirm_button = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.LINK_TEXT, "Confirm")))
                    Confirm_button.click()

                    date = datetime(
                        year=int(month_year.split(" ")[1]),
                        month=datetime.strptime(month_year.split(" ")[0], "%B").month,
                        day=int(td_text)
                    )

                    last_date_update(date)
                    driver.quit()
                    exit(0)

                    time.sleep(5)


        # Find "Next" button
        next_button = driver.find_element(By.CLASS_NAME, "ui-datepicker-next")

        # Click the "Next" button to move to the next month
        next_button.click()
        time.sleep(1)  # Wait for the UI to update


        #tie this at the end
        if month_year == "December 2025":
            break

    refresh_and_wait(driver, (By.ID, "appointments_consulate_appointment_date"))
