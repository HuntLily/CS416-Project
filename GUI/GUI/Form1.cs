using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GUI
{
    public partial class chiSquared : Form
    {
        public chiSquared()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                OpenFileDialog dialog = new OpenFileDialog();
                dialog.ShowDialog();
                string sourceURL = "";

                if(dialog.FileName != "")
                {
                    if(dialog.FileName.EndsWith(".csv"))
                    {
                        MessageBox.Show("works");
                        return;
                    }
                    else
                    {
                        MessageBox.Show("Error with file type, please upload a .csv file.");
                        return;
                    }
                }


            }
            catch(Exception ex)
            {
                MessageBox.Show("Error " + ex);
            }



        }

        private void helpButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("To import a csv file press the import button which will open up your file explorer, To " +
                "calculate the press the calculate button");
        }
    }
}
