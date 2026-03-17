namespace main
{
    class To_Do_Item
    {
        private string due_Date;
        public string Due_Date
        {
            get { return due_Date; }
            set { due_Date = value; }
        }

        private string description;
        public string Description
        {
            get { return description; }
            set { description = value; }
        }

        public To_Do_Item(string due, string desc)
        {
            due_Date = due;
            description = desc;
        }
    }

    class Day_List
    {
        private List<To_Do_Item> day_List;
        public List<To_Do_Item> day_LIST
        {
            get { return day_List; }
            set { day_List = value; }
        }

        public Day_List() => day_List = new List<To_Do_Item>();
    }

    class Month_List
    {
        private List<Day_List> item_Lists;
        public List<Day_List> item_ListS
        {
            get { return item_Lists; }
            set { item_Lists = value; }
        }

        // Pre-fill the list with 32 null slots (indices 0 to 31)
        public Month_List()
        {
            item_Lists = new List<Day_List>();
            for (int i = 0; i <= 31; i++)
            {
                item_Lists.Add(null);
            }
        }
    }

    class main
    {
        static void Main(string[] args)
        {
            int selection;
            string date;
            string[] parts;
            string desc;
            int day;

            Dictionary<int, Month_List> Journal = new Dictionary<int, Month_List>();

            while (true)
            {
                Console.Clear();

                Console.WriteLine("Welcome To Your To Do List!:\n" +
                    "1- Add a new item to the list\n" +
                    "2- Display the list\n" +
                    "3- Exit\n" +
                    "Please Enter Selection:");

                selection = int.Parse(Console.ReadLine());

                Console.Clear();

                switch (selection)
                {
                    case 1:
                        Console.WriteLine("Please enter the date in M/D/Y format:");
                        date = Console.ReadLine();
                        parts = date.Split("/");
                        int month = int.Parse(parts[0]);
                        day = int.Parse(parts[1]);
                        int year = int.Parse(parts[2]);
                        int key = jointtwonumber(month, year);

                        // Create the Month_List if it doesn't exist
                        if (!Journal.ContainsKey(key))
                        {
                            Month_List newMonth = new Month_List();
                            Journal.Add(key, newMonth);
                        }

                        // assign a new Day_List if needed
                        if (Journal[key].item_ListS[day] == null)
                        {
                            Journal[key].item_ListS[day] = new Day_List();
                        }

                        Console.WriteLine("Please enter the description of this to do:");
                        desc = Console.ReadLine();
                        To_Do_Item new_Item = new To_Do_Item(date, desc);

                        // Use direct indexing to add the new item
                        Journal[key].item_ListS[day].day_LIST.Add(new_Item);
                        break;

                    case 2:
                        Console.WriteLine("Please enter Month/Year in this format (e.g., 4/2025):");
                        string value = Console.ReadLine();
                        string[] helper = value.Split("/");
                        int displayMonth = int.Parse(helper[0]);
                        int displayYear = int.Parse(helper[1]);
                        int displayKey = jointtwonumber(displayMonth, displayYear);

                        Console.Clear();

                        if (!Journal.ContainsKey(displayKey))
                        {
                            Console.WriteLine("No entries for this month.");
                            break;
                        }

                        Month_List curr_Page = Journal[displayKey];

                        // Loop through day slots 1 to 31 (index 0 is unused)
                        for (int i = 1; i <= 31; i++)
                        {
                            if (curr_Page.item_ListS[i] == null)
                                continue;

                            foreach (var element in curr_Page.item_ListS[i].day_LIST)
                            {
                                Console.WriteLine(element.Due_Date + "     " + element.Description);
                            }
                        }

                        Console.ReadKey();
                        break;

                    case 3:
                        return;

                    default:
                        Console.WriteLine("Invalid selection. Please try again.");
                        break;
                }
            }
        }

        // key generator: formats month as two digits to ensure consistency
        static int jointtwonumber(int a, int b)
        {
            return int.Parse($"{a:D2}{b}");
        }
    }
}
