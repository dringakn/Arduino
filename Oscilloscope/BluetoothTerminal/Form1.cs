using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

using System.Windows.Forms;

namespace BluetoothTerminal
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            ChangeDTR();            
            cmbPort1.DataSource = SerialPort.GetPortNames();
            cmbPort2.DataSource = SerialPort.GetPortNames();
            Properties.Settings.Default.Reload();
            cmbPort1.Text = Properties.Settings.Default.Port1;
            cmbPort2.Text = Properties.Settings.Default.Port2;
            txtBaud.Text = Properties.Settings.Default.Baud;
            txtPort1Data1.Text = Properties.Settings.Default.Text11;
            txtPort1Data2.Text = Properties.Settings.Default.Text12;
            txtPort1Data3.Text = Properties.Settings.Default.Text13;
            txtPort1Data4.Text = Properties.Settings.Default.Text14;
            txtPort1Data5.Text = Properties.Settings.Default.Text15;
            txtPort2Data1.Text = Properties.Settings.Default.Text21;
            txtPort2Data2.Text = Properties.Settings.Default.Text22;
            txtPort2Data3.Text = Properties.Settings.Default.Text23;
            txtPort2Data4.Text = Properties.Settings.Default.Text24;
            txtPort2Data5.Text = Properties.Settings.Default.Text25;
        }

        void ConnectSerialPort()
        {
            if (sp1.IsOpen)
            {
                sp1.Close();
                if(sp2.IsOpen)sp2.Close();
                btnConnect.Text = "Connect";
                btnDTR.Enabled = false;
                txtPort1Data1.Enabled = txtPort1Data2.Enabled = txtPort1Data3.Enabled = txtPort1Data4.Enabled = txtPort1Data5.Enabled = false;
                txtPort2Data1.Enabled = txtPort2Data2.Enabled = txtPort2Data3.Enabled = txtPort2Data4.Enabled = txtPort2Data5.Enabled = false;
            }
            else
            {   
                sp1.PortName = cmbPort1.SelectedItem.ToString();
                sp2.PortName = cmbPort2.SelectedItem.ToString();
                sp1.BaudRate = sp2.BaudRate = Convert.ToInt32(txtBaud.Text);
                //MessageBox.Show((sp1.PortName!=sp2.PortName).ToString());
                sp1.NewLine = sp2.NewLine = "\r\n";
                sp1.Open();
                if(sp1.PortName!=sp2.PortName)sp2.Open();
                btnConnect.Text = "DisConnect";
                btnDTR.Enabled = true;
                btnDTR.Text = "DTR: " + sp1.DtrEnable.ToString();
                txtPort1Data1.Enabled = txtPort1Data2.Enabled = txtPort1Data3.Enabled = txtPort1Data4.Enabled = txtPort1Data5.Enabled = true;
                txtPort2Data1.Enabled = txtPort2Data2.Enabled = txtPort2Data3.Enabled = txtPort2Data4.Enabled = txtPort2Data5.Enabled = true;
                saveParameters();
            }
        }

        void ChangeDTR()
        {
            if (sp1.IsOpen)
            {
                if (sp1.DtrEnable)
                {
                    sp1.DtrEnable = sp2.DtrEnable = false;
                    btnDTR.Text = "DTR: " + sp1.DtrEnable.ToString();
                }
                else
                {
                    sp1.DtrEnable = sp2.DtrEnable = true;
                    btnDTR.Text = "DTR: " + sp1.DtrEnable.ToString();
                }
            }
            else
            {
                btnDTR.Enabled = false;
                btnDTR.Text = "DTR: " + sp1.DtrEnable.ToString();
                txtPort1Data1.Enabled = txtPort1Data2.Enabled = txtPort1Data3.Enabled = txtPort1Data4.Enabled = txtPort1Data5.Enabled = false;
                txtPort2Data1.Enabled = txtPort2Data2.Enabled = txtPort2Data3.Enabled = txtPort2Data4.Enabled = txtPort2Data5.Enabled = false;
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            ConnectSerialPort();
        }

        private void btnScanPorts_Click(object sender, EventArgs e)
        {
            cmbPort1.DataSource = SerialPort.GetPortNames();
            cmbPort2.DataSource = SerialPort.GetPortNames();
        }

        private void btnDTR_Click(object sender, EventArgs e)
        {
            ChangeDTR();
        }

        private void btnClearTerminal_Click(object sender, EventArgs e)
        {
            rtbPort1.Clear();
            rtbPort2.Clear();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (sp1.IsOpen)
            {
                string str = sp1.ReadExisting();
                rtbPort1.AppendText(str);
                if(str.Length>0) rtbPort1.ScrollToCaret();
                //rtbPort1.Select(rtbPort1.Text.Length, 0);
            }
            if (sp2.IsOpen)
            {
                string str = sp2.ReadExisting();
                rtbPort2.AppendText(str);
                if(str.Length>0) rtbPort2.ScrollToCaret();
                //rtbPort2.Select(rtbPort2.Text.Length, 0);
            }
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            saveParameters();
        }

        void saveParameters()
        {
            Properties.Settings.Default.Port1 = sp1.PortName;
            Properties.Settings.Default.Port2 = sp2.PortName;
            Properties.Settings.Default.Baud = sp1.BaudRate.ToString();
            Properties.Settings.Default.Text11 = txtPort1Data1.Text;
            Properties.Settings.Default.Text12 = txtPort1Data2.Text;
            Properties.Settings.Default.Text13 = txtPort1Data3.Text;
            Properties.Settings.Default.Text14 = txtPort1Data4.Text;
            Properties.Settings.Default.Text15 = txtPort1Data5.Text;
            Properties.Settings.Default.Text21 = txtPort2Data1.Text;
            Properties.Settings.Default.Text22 = txtPort2Data2.Text;
            Properties.Settings.Default.Text23 = txtPort2Data3.Text;
            Properties.Settings.Default.Text24 = txtPort2Data4.Text;
            Properties.Settings.Default.Text25 = txtPort2Data5.Text;
            Properties.Settings.Default.Save();
        }

        private void txtPort1Data1_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                TextBox tb = (TextBox)sender;
                if (sp1.IsOpen)
                    sp1.WriteLine(tb.Text);
            }
        }

        private void txtPort2Data1_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                TextBox tb = (TextBox)sender;
                if (sp2.IsOpen)
                    sp2.WriteLine(tb.Text);
            }
        }
    }
}
