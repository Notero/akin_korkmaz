import requests

# Define necessary headers
headers = {
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7)",
    "Referer": "https://ais.usvisa-info.com/en-tr/niv/schedule/65864555/appointment",
    "X-Requested-With": "XMLHttpRequest",
    "X-CSRF-Token": "3KL7mIWDad0obruK7BmW8exsvw66L23Nwnv6+VjLU0UjVGi6urHaMP+qSvBjf9n0jway1UuP8tkCyqk44Dkf+A==",  # Update dynamically
    "Cookie": "_yatri_session=1bRVM4h%2Fz83o375VKI61LIk%2FEIxsaNAEWfgzInFa2yNYQVw%2FPxA%2FBuf27nOsq%2BE1s5neq2Hp37GRN9k1oqvQ%2ByqL6omwppCDXliMi0UeesVOnC%2B9bkJzUWaRdBaQQv0XnjlkTaGa0gLxBLq%2B0YQbCBbllVdIXQcK0q9pE8%2B%2FlkQeb6RbGv3jNk33ZjNXnZ42%2F7Sj9%2FRlw4R9FB5ZoEVdkxkM5JMMp7wZsUDop%2B1apN%2BIOE5qEXEL%2FcZjnh2SdlYyp6pH5MuZ0%2BY1E7KFTDHqx52MQj5XxlZU2xY8TojfD9jhojYlpb3v3yNTI5yS3F8QHv6n2qgFjcvQOWtsiQDz7T0CDri9zIkI8aV%2FmtCFErAmbJFApg8F2ejaXN3vdITFcevUAl7wPmR8N3Gb6EMNunPgrBVzm0tX3aRche%2FkBxeG8zvHmwpUs7Q%2Bwxx21ButHc3IrX7bUHqcnkhKiWP4xIDkNoiMbpUtgL8j%2FZor7DP3oA0zZe3NGgTtetBYeBYazp5nbBBqE%2FXmqXmm4f8rGJ0fCMQyHIAYsvWlvMhJFUXh5glZTwCNsxzEm9hN0nmQbwPXtHvj0d5AJBgJkKfDYyZ3NFQ1OLAse09TbuAKG5QUcZbFvA7%2BCK9kFbW2UIbiIPh8f7wDDvZ%2BFT74hD5mQzcMUPfkbzvoOveKHUoJBfAnynjQQgKZQBUSmR8CvQO9MSJjHTofbyIilpYhE7WuDHyV7xq609IfCkVYMBurJOXKnICEJGGh0M9kXuUidxbrgOd5VkuMmLVeGOaq1%2BaXg9SbfrXFG1dFOYe4ZOKQKocSRBwW2b6he%2BvU0hsXcVWZ4uA%3D--V%2Bam9VywW5wnXQut--iwHoCEuksexYa%2FoL2vvXHw%3D%3D"  # Replace with actual session cookie
}

# API endpoint for available appointment dates
url = "https://ais.usvisa-info.com/en-tr/niv/schedule/65864555/appointment/days/125.json?appointments[expedite]=false"

def get_first_available_date():
    response = requests.get(url, headers=headers)

    if response.status_code == 200:
        available_dates = response.json()
        if available_dates:
            first_date = available_dates[0]["date"]  # Extract the first available date
            print(f"First available appointment date: {first_date}")
            return first_date
        else:
            print("No available dates at the moment.")
            return None
    else:
        print(f"Failed to fetch data: {response.status_code}")
        return None

# Run function to fetch the first available date
get_first_available_date()
