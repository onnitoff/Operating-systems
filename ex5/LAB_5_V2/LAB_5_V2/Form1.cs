using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.NetworkInformation;
using System.Management;

namespace LAB_5_V2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        ////////// Информация о накопителях //////////
        private void button1_Click(object sender, EventArgs e)
        {
            
            DriveInfo[] drives = DriveInfo.GetDrives();
            int i = 1;
            listView1.Clear();
            listView1.Columns.Add("№", 60, HorizontalAlignment.Center);
            listView1.Columns.Add("Название", 120, HorizontalAlignment.Left);
            listView1.Columns.Add("Тип", 120, HorizontalAlignment.Left);
            listView1.Columns.Add("Объем", 160, HorizontalAlignment.Center);
            listView1.Columns.Add("Свободно", 160, HorizontalAlignment.Center);
            listView1.Columns.Add("Метка", 120, HorizontalAlignment.Center);
            listView1.Columns.Add("Файловая система", 120, HorizontalAlignment.Center);

            foreach (DriveInfo drive in drives)
            {

                ListViewItem item1 = new ListViewItem(i.ToString(), 0);

                item1.SubItems.Add(drive.Name);                             
                item1.SubItems.Add(drive.DriveType.ToString());                           
                item1.SubItems.Add(drive.TotalSize.ToString());
                item1.SubItems.Add(drive.TotalFreeSpace.ToString());
                item1.SubItems.Add(drive.VolumeLabel);
                item1.SubItems.Add(drive.DriveFormat.ToString());

                listView1.Items.AddRange(new ListViewItem[] { item1});
                i++;

            }
        }

        ////////// Информация о сетевых устройствах //////////
        private void button2_Click(object sender, EventArgs e)
        {
            NetworkInterface[] nInterfaces = NetworkInterface.GetAllNetworkInterfaces();
            int i = 1;

            listView1.Clear();

            listView1.Columns.Add("№", 60, HorizontalAlignment.Center);
            listView1.Columns.Add("Описание", 160, HorizontalAlignment.Left);
            listView1.Columns.Add("Тип", 120, HorizontalAlignment.Left);
            listView1.Columns.Add("Имя", 160, HorizontalAlignment.Left);
            listView1.Columns.Add("MAC", 120, HorizontalAlignment.Center);
            listView1.Columns.Add("Состояние", 80, HorizontalAlignment.Center);
            listView1.Columns.Add("Скорость", 160, HorizontalAlignment.Center);

            foreach (NetworkInterface nInterface in nInterfaces)
            {

                ListViewItem item1 = new ListViewItem(i.ToString(), 0);

                item1.SubItems.Add(nInterface.Description.ToString());
                item1.SubItems.Add(nInterface.NetworkInterfaceType.ToString());
                item1.SubItems.Add(nInterface.Name.ToString());               
                item1.SubItems.Add(nInterface.GetPhysicalAddress().ToString());
                item1.SubItems.Add(nInterface.OperationalStatus.ToString());
                item1.SubItems.Add(nInterface.Speed.ToString());

                listView1.Items.AddRange(new ListViewItem[] { item1 });
                i++;

            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            List<string> param = new List<string>();
            param.Add("Name");
            param.Add("Manufacturer");
            param.Add("Description");
            var result = GetHardwareInfo("Win32_Processor", param);
            int i = 1;

            

            listView1.Clear();

            listView1.Columns.Add("№", 60, HorizontalAlignment.Center);
            listView1.Columns.Add("Имя", 260, HorizontalAlignment.Left);
            listView1.Columns.Add("Производитель", 160, HorizontalAlignment.Left);
            listView1.Columns.Add("Описание", 200, HorizontalAlignment.Left);

            if (result.Count == 3)
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);

                item1.SubItems.Add(result[0].ToString());
                item1.SubItems.Add(result[1].ToString());
                item1.SubItems.Add(result[2].ToString());

                listView1.Items.AddRange(new ListViewItem[] { item1 });
                i++;
            }
            else
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);
                item1.SubItems.Add("Error".ToString());
                listView1.Items.AddRange(new ListViewItem[] { item1 });
            }
        }


        private static List<string> GetHardwareInfo(string WIN32_Class, List<string> ClassItemField)
        {
            List<string> result = new List<string>();

            ManagementObjectSearcher searcher = new ManagementObjectSearcher("SELECT * FROM " + WIN32_Class);

            try
            {
                foreach (ManagementObject obj in searcher.Get())
                {
                    foreach (var item in ClassItemField)
                    {
                        result.Add(obj[item].ToString().Trim());
                    }
                    
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            return result;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            List<string> param = new List<string>();
            param.Add("Name");
            param.Add("VideoProcessor");
            param.Add("DriverVersion");
            param.Add("AdapterRAM");
            var result = GetHardwareInfo("Win32_VideoController", param);
            int i = 1;



            listView1.Clear();

            listView1.Columns.Add("№", 60, HorizontalAlignment.Center);
            listView1.Columns.Add("Видеокарта", 260, HorizontalAlignment.Left);
            listView1.Columns.Add("Видеопроцессор", 260, HorizontalAlignment.Left);
            listView1.Columns.Add("Версия драйвера", 200, HorizontalAlignment.Left);
            listView1.Columns.Add("Объем памяти в байтах", 200, HorizontalAlignment.Left);

            if (result.Count == 8)
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);

                item1.SubItems.Add(result[0].ToString());
                item1.SubItems.Add(result[1].ToString());
                item1.SubItems.Add(result[2].ToString());
                item1.SubItems.Add(result[3].ToString());

                listView1.Items.AddRange(new ListViewItem[] { item1 });
                i++;

                ListViewItem item2 = new ListViewItem(i.ToString(), 0);

                item2.SubItems.Add(result[4].ToString());
                item2.SubItems.Add(result[5].ToString());
                item2.SubItems.Add(result[6].ToString());
                item2.SubItems.Add(result[7].ToString());

                listView1.Items.AddRange(new ListViewItem[] { item2 });
                i++;
            }
            else
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);
                item1.SubItems.Add("Error".ToString());
                listView1.Items.AddRange(new ListViewItem[] { item1 });
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            List<string> param = new List<string>();
            param.Add("Name");
            param.Add("Manufacturer");
            param.Add("Product");
            param.Add("Version");
            var result = GetHardwareInfo("Win32_BaseBoard", param);
            int i = 1;



            listView1.Clear();

            listView1.Columns.Add("№", 60, HorizontalAlignment.Center);
            listView1.Columns.Add("Материнская плата", 260, HorizontalAlignment.Left);
            listView1.Columns.Add("Производитель", 260, HorizontalAlignment.Left);
            listView1.Columns.Add("Модель", 200, HorizontalAlignment.Left);
            listView1.Columns.Add("Версия", 200, HorizontalAlignment.Left);

            if (result.Count > 0)
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);

                item1.SubItems.Add(result[0].ToString());
                item1.SubItems.Add(result[1].ToString());
                item1.SubItems.Add(result[2].ToString());
                item1.SubItems.Add(result[3].ToString());

                listView1.Items.AddRange(new ListViewItem[] { item1 });
                i++;
            }
            else
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);
                item1.SubItems.Add("Error".ToString());
                listView1.Items.AddRange(new ListViewItem[] { item1 });
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            List<string> param = new List<string>();
            param.Add("Name");
            param.Add("Manufacturer");
            param.Add("SerialNumber");
            param.Add("Version");
            var result = GetHardwareInfo("Win32_BIOS", param);
            int i = 1;



            listView1.Clear();

            listView1.Columns.Add("№", 60, HorizontalAlignment.Center);
            listView1.Columns.Add("BIOS", 160, HorizontalAlignment.Left);
            listView1.Columns.Add("Производитель", 260, HorizontalAlignment.Left);
            listView1.Columns.Add("Серийный номер", 200, HorizontalAlignment.Left);
            listView1.Columns.Add("Версия", 200, HorizontalAlignment.Left);

            if (result.Count > 0)
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);

                item1.SubItems.Add(result[0].ToString());
                item1.SubItems.Add(result[1].ToString());
                item1.SubItems.Add(result[2].ToString());
                item1.SubItems.Add(result[3].ToString());

                listView1.Items.AddRange(new ListViewItem[] { item1 });
                i++;
            }
            else
            {
                ListViewItem item1 = new ListViewItem(i.ToString(), 0);
                item1.SubItems.Add("Error".ToString());
                listView1.Items.AddRange(new ListViewItem[] { item1 });
            }
        }
    }
}
