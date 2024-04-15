using System;
using System.Data.SqlClient;

namespace PopulationManagementApp
{
    class Program
    {
        static string connectionString = "Your_Connection_String_Here";

        static void Main(string[] args)
        {
            Console.WriteLine("Welcome to Population Management App!");

            while (true)
            {
                Console.WriteLine("\n1. Add a country and its regions");
                Console.WriteLine("0. Exit");

                Console.Write("Enter your choice: ");
                int choice = int.Parse(Console.ReadLine());

                switch (choice)
                {
                    case 1:
                        AddCountryAndRegions();
                        break;
                    case 0:
                        Environment.Exit(0);
                        break;
                    default:
                        Console.WriteLine("Invalid choice. Please try again.");
                        break;
                }
            }
        }

        static void AddCountryAndRegions()
        {
            Console.WriteLine("\nEnter country name:");
            string countryName = Console.ReadLine();

            Console.WriteLine("Enter number of regions:");
            int numRegions = int.Parse(Console.ReadLine());

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();

                // Insert country into Countries table
                string insertCountryQuery = $"INSERT INTO Countries (Name) VALUES ('{countryName}')";
                SqlCommand insertCountryCommand = new SqlCommand(insertCountryQuery, connection);
                insertCountryCommand.ExecuteNonQuery();

                // Get the ID of the inserted country
                string getCountryIDQuery = "SELECT SCOPE_IDENTITY()";
                SqlCommand getCountryIDCommand = new SqlCommand(getCountryIDQuery, connection);
                int countryID = Convert.ToInt32(getCountryIDCommand.ExecuteScalar());

                // Insert regions into Regions table
                for (int i = 1; i <= numRegions; i++)
                {
                    Console.WriteLine($"\nEnter name of region {i}:");
                    string regionName = Console.ReadLine();

                    Console.WriteLine($"Enter population of region {i}:");
                    int population = int.Parse(Console.ReadLine());

                    string insertRegionQuery = $"INSERT INTO Regions (Name, Population, CountryID) VALUES ('{regionName}', {population}, {countryID})";
                    SqlCommand insertRegionCommand = new SqlCommand(insertRegionQuery, connection);
                    insertRegionCommand.ExecuteNonQuery();
                }

                Console.WriteLine("Country and regions added successfully!");
            }
        }
    }
}
