﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

using System.Windows.Forms;

namespace Robot_Control_Terminal
{

    public partial class Form1 : Form
    {
        private bool parseRxData = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            SerialPortConnection(true);
        }

        void saveParameters()
        {
            Properties.Settings.Default.Port = sp.PortName;
            Properties.Settings.Default.Save();
        }

        void loadParameters()
        {
            cmbPort.DataSource = SerialPort.GetPortNames();
            cmbPort.Text = Properties.Settings.Default.Port;
        }

        void SerialPortConnection(bool bInit=false)
        {
            if (sp.IsOpen || bInit)
            {
                if (sp.IsOpen)
                {
                    try
                    {
                        sp.Close();
                    }
                    catch (Exception ex)
                    {
                        cmbPort.DataSource = SerialPort.GetPortNames();
                    }
                }
                loadParameters();
                btnConnect.Text = "Connect";
                btnDTR.Text = "Reset [DTR:" + sp.DtrEnable.ToString() + "]";
                btnReadAllSensors.Enabled = false;
                btnReadOdometry.Enabled = false;
                btnReadUltrasonic.Enabled = false;
                btnReadInfrared.Enabled = false;
                btnReadEncoder.Enabled = false;
                btnReadPID.Enabled = false;
                btnHelp.Enabled = false;
                btnSetSamples.Enabled = false;
                btnSetThreshold.Enabled = false;
                btnSetOdometricConstants.Enabled = false;
                btnSetPID.Enabled = false;
                btnResetIR.Enabled = false;
                btnResetOdometry.Enabled = false;
                btnResetRobot.Enabled = false;
                btnMotorCloseLoop.Enabled = false;
                btnMotorOpenLoop.Enabled = false;
                btnMotorStop.Enabled = false;
                txtTime.Enabled = false;
                txtV.Enabled = false;
                txtW.Enabled = false;
                txtIRCalibLeft.Enabled = false;
                txtIRCalibMiddleLeft.Enabled = false;
                txtIRCalibMiddle.Enabled = false;
                txtIRCalibMiddleRight.Enabled = false;
                txtIRCalibRight.Enabled = false;
                txtKp.Enabled = false;
                txtKi.Enabled = false;
                txtKd.Enabled = false;
                txtKv.Enabled = false;
                txtKw.Enabled = false;
                txtKwos.Enabled = false;
                txtVSamples.Enabled = false;
                txtIRSamples.Enabled = false;
                txtUSSamples.Enabled = false;
                txtIRThreshold.Enabled = false;
                txtUSFrontThreshold.Enabled = false;
                txtUSSideThreshold.Enabled = false;
                btnDTR.Enabled = false;
            }
            else
            {
                try
                {
                    sp.PortName = cmbPort.SelectedItem.ToString();
                    sp.BaudRate = 115200;
                    sp.StopBits = StopBits.One;
                    sp.Parity = Parity.None;
                    sp.DataBits = 8;
                    sp.NewLine = "\r\n";
                    sp.Open();
                    btnConnect.Text = "DisConnect";
                    btnDTR.Text = "Reset [DTR:" + sp.DtrEnable.ToString() + "]";
                    btnReadAllSensors.Enabled = true;
                    btnReadOdometry.Enabled = true;
                    btnReadUltrasonic.Enabled = true;
                    btnReadInfrared.Enabled = true;
                    btnReadEncoder.Enabled = true;
                    btnReadPID.Enabled = true;
                    btnHelp.Enabled = true;
                    btnSetSamples.Enabled = true;
                    btnSetThreshold.Enabled = true;
                    btnSetOdometricConstants.Enabled = true;
                    btnSetPID.Enabled = true;
                    btnResetIR.Enabled = true;
                    btnResetOdometry.Enabled = true;
                    btnResetRobot.Enabled = true;
                    btnMotorCloseLoop.Enabled = true;
                    btnMotorOpenLoop.Enabled = true;
                    btnMotorStop.Enabled = true;
                    txtTime.Enabled = true;
                    txtV.Enabled = true;
                    txtW.Enabled = true;
                    //txtIRCalibLeft.Enabled = true;
                    //txtIRCalibMiddleLeft.Enabled = true;
                    //txtIRCalibMiddle.Enabled = true;
                    //txtIRCalibMiddleRight.Enabled = true;
                    //txtIRCalibRight.Enabled = true;
                    txtKp.Enabled = true;
                    txtKi.Enabled = true;
                    txtKd.Enabled = true;
                    txtKv.Enabled = true;
                    txtKw.Enabled = true;
                    txtKwos.Enabled = true;
                    txtVSamples.Enabled = true;
                    txtIRSamples.Enabled = true;
                    txtUSSamples.Enabled = true;
                    txtIRThreshold.Enabled = true;
                    txtUSFrontThreshold.Enabled = true;
                    txtUSSideThreshold.Enabled = true;
                    btnDTR.Enabled = true;
                    saveParameters();
                }
                catch (Exception ex)
                {
                    cmbPort.DataSource = SerialPort.GetPortNames();
                }
            }

        }

        private void tmrDataPoll_Tick(object sender, EventArgs e)
        {
            if (sp.IsOpen)
            {
                string str = sp.ReadExisting();
                rtbPort.AppendText(str);
                if (str.Length > 0) rtbPort.ScrollToCaret();                
                if (parseRxData)
                {
                    //string[] words = { "Kp:", "Ki:", "Kd:" };
                    //HighlightWords(words);
                    string word = "Kp: ";
                    //int wordStartIndex = rtbPort.Find(word, RichTextBoxFinds.Reverse);
                    //if (wordStartIndex != -1)
                    //{
                    //    rtbPort.SelectionStart = wordStartIndex;
                    //    rtbPort.SelectionLength = word.Length;
                    //    rtbPort.SelectionBackColor = Color.Yellow;
                    //    txtKp.Text = rtbPort.Text.Substring(wordStartIndex + word.Length, 3);
                    parseRxData = false;
                    //}
                    //String pattern = "\\d+";
                    //Pattern p = Pattern.compile(pattern);
                    //Matcher m = p.matcher(rtbPort.Text);

                    //if(m.find())
                    //{
                    //    MessageBox.Show(m.group(1));
                    //}
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            saveParameters();
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            SerialPortConnection();
        }

        private void txtCommand_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode==Keys.Enter)
            {
                sendData(txtCommand.Text);
            }
        }

        private void btnClearTerminal_Click(object sender, EventArgs e)
        {
            rtbPort.Clear();
        }

        private void cmbPort_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            cmbPort.DataSource = SerialPort.GetPortNames();
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            sendData("h?");
            parseRxData = true;
        }

        private void HighlightWords(string[] words)
        {
            foreach (string word in words)
            {
                int startIndex = 0;
                while (startIndex < rtbPort.TextLength)
                {

                    int wordStartIndex = rtbPort.Find(word, startIndex, RichTextBoxFinds.Reverse);
                    if (wordStartIndex != -1)
                    {
                        rtbPort.SelectionStart = wordStartIndex;
                        rtbPort.SelectionLength = word.Length;
                        rtbPort.SelectionBackColor = Color.Yellow;
                    }
                    else
                        break;
                    startIndex += wordStartIndex + word.Length;
                }
            }
        }

        void sendData (string data)
        {
            if (sp.IsOpen)
            {
                sp.WriteLine(data);
            }
        }

        private void btnReadAllSensors_Click(object sender, EventArgs e)
        {
            sendData("ls");
        }

        private void btnReadOdometry_Click(object sender, EventArgs e)
        {
            sendData("lo");
        }

        private void btnReadUltrasonic_Click(object sender, EventArgs e)
        {
            sendData("lu");
        }

        private void btnReadInfrared_Click(object sender, EventArgs e)
        {
            sendData("li");
        }

        private void btnMotorStop_Click(object sender, EventArgs e)
        {
            sendData("ms");
        }

        private void btnResetOdometry_Click(object sender, EventArgs e)
        {
            sendData("ro");
        }

        private void btnResetRobot_Click(object sender, EventArgs e)
        {
            sendData("rr");
        }

        private void btnResetIR_Click(object sender, EventArgs e)
        {
            sendData("ri");
        }

        private void btnMotorCloseLoop_Click(object sender, EventArgs e)
        {
            sendData("mc " + txtV.Text + " " + txtW.Text + " " + txtTime.Text);
        }

        private void btnMotorOpenLoop_Click(object sender, EventArgs e)
        {
            sendData("mo " + txtV.Text + " " + txtW.Text + " " + txtTime.Text);
        }

        private void btnReadEncoder_Click(object sender, EventArgs e)
        {
            sendData("le");
        }

        private void btnReadPID_Click(object sender, EventArgs e)
        {
            sendData("lp");
        }

        private void btnDTR_Click(object sender, EventArgs e)
        {
            if (sp.IsOpen)
            {
                if (sp.DtrEnable)
                    sp.DtrEnable = false;
                else
                    sp.DtrEnable = true;
                btnDTR.Text = "Reset [DTR:" + sp.DtrEnable.ToString() + "]";
            }
        }

        private void btnSetSamples_Click(object sender, EventArgs e)
        {
            sendData("sf " + txtVSamples.Text + " " + txtIRSamples.Text + " " + txtUSSamples.Text);
        }

        private void btnSetThreshold_Click(object sender, EventArgs e)
        {
            sendData("st " + txtIRThreshold.Text + " " + txtUSFrontThreshold.Text + " " + txtUSSideThreshold.Text);
        }

        private void btnSetOdometricConstants_Click(object sender, EventArgs e)
        {
            sendData("sk " + txtKv.Text + " " + txtKw.Text + " " + txtKwos.Text);
        }

        private void btnSetPID_Click(object sender, EventArgs e)
        {
            sendData("sc " + txtKp.Text + " " + txtKi.Text + " " + txtKd.Text);
        }
    }
}
