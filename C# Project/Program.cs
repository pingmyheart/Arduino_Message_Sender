using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO.Ports;//include the library to manage the serial ports

namespace Console
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPort serialPort = new SerialPort();
            serialPort.BaudRate = 9600;//set the baudRate of the port that is the same in the Arduino Source Code

            string prefix;
            string number;
            string textMessage;
            string[] ports = SerialPort.GetPortNames();//put into an array the name of each serial connected to the pc
            foreach(string port in ports)
            {
                System.Console.WriteLine(port);//print each portName contenuted into the array
            }
            System.Console.WriteLine();
            System.Console.WriteLine("Select a port");
            serialPort.PortName = System.Console.ReadLine().ToUpper();//convert into UPPER CASE the name in input of the port
            System.Console.WriteLine("Set national prefix without +");
            prefix = System.Console.ReadLine();
            System.Console.WriteLine("Set telephone number");
            number = System.Console.ReadLine();
            System.Console.WriteLine("Set message to be sent");
            textMessage = System.Console.ReadLine();
            System.Console.WriteLine("You're message is going to be passed to the Arduino Message Sender Centre");
            serialPort.Open();
            serialPort.WriteLine(prefix + '`' + number + '`' + textMessage);
            serialPort.Close();
            System.Console.WriteLine();
            System.Console.WriteLine("Message Correctly Sent to the System Manager");
            System.Console.WriteLine();
            System.Console.WriteLine("Press Enter to Logout");
            System.Console.ReadLine();
        }
    }
}
