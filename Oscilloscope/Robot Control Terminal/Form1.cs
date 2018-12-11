using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Text.RegularExpressions;

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
            // Create the ToolTip and associate with the Form container.
            ToolTip toolTip1 = new ToolTip();

            // Set up the delays for the ToolTip.
            toolTip1.AutoPopDelay = 20000;
            toolTip1.InitialDelay = 500;
            toolTip1.ReshowDelay = 500;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTip1.ShowAlways = true;

            toolTip1.SetToolTip(this.txtV, "Left Wheel Velocity(OpenLoop)[-100 to 100]/Linear Velocity(CloseLoop)[-30 to 30 Cm/Sec]");
            toolTip1.SetToolTip(this.lblV, "Left Wheel Velocity(OpenLoop)[-100 to 100]/Linear Velocity(CloseLoop)[-30 to 30 Cm/Sec]");

            toolTip1.SetToolTip(this.txtW, "Right Wheel Velocity(OpenLoop)[-100 to 100]/Angular Velocity(CloseLoop)[-PI/2 to PI/2 Rad/Sec]");
            toolTip1.SetToolTip(this.lblW, "Right Wheel Velocity(OpenLoop)[-100 to 100]/Angular Velocity(CloseLoop)[-PI/2 to PI/2 Rad/Sec]");

            toolTip1.SetToolTip(this.txtTime, "Command execution time in millisecond [0 to 1000000 milliSeconds, -1 for infinite time]");
            toolTip1.SetToolTip(this.lblTime, "Command execution time in millisecond [0 to 1000000 milliSeconds, -1 for infinite time]");

            toolTip1.SetToolTip(this.txtVSamples, "Number of samples for velocity smoothing [1 to 10]");
            toolTip1.SetToolTip(this.txtIRSamples, "Number of samples for Infrared measurements smoothing [1 to 10]");
            toolTip1.SetToolTip(this.txtUSSamples, "Number of samples for Ulstrasonic measurements smoothing [1 to 10]");

            toolTip1.SetToolTip(this.txtIRThreshold, "Infrared sensor threshold for line detection [0 to 1023]");
            toolTip1.SetToolTip(this.txtUSFrontThreshold, "Front ultrasonic sensor threshold for obstacle detection [0 to 600 Cm]");
            toolTip1.SetToolTip(this.txtUSSideThreshold, "Right and Left ultrasonic sensor threshold for obstacle detection [0 to 600 Cm]");

            toolTip1.SetToolTip(this.txtKv, "Linear velocity claibration constant [0 to 10, default value is 1]");
            toolTip1.SetToolTip(this.txtKw, "Angular velocity claibration constant [0 to 10, default value is 1]");
            toolTip1.SetToolTip(this.txtKwos, "Angular velocity offset for straight line motion [-10 to 10, default value is 0]");

            toolTip1.SetToolTip(this.txtKp, "Kp, propotional constant [0 to 10000]");
            toolTip1.SetToolTip(this.txtKi, "Ki, integration constant [0 to 10000]");
            toolTip1.SetToolTip(this.txtKd, "Kd, derivative constant [0 to 10000]");

            toolTip1.SetToolTip(this.txtBaud, "Serial port communication speed [default value is 115200]");
            toolTip1.SetToolTip(this.btnHelp, "Show Help");
            toolTip1.SetToolTip(this.btnDTR, "Robot hardware reset");

        }

        void saveParameters()
        {
            Properties.Settings.Default.Port = sp.PortName;
            Properties.Settings.Default.Baud = sp.BaudRate.ToString();
            Properties.Settings.Default.Save();
        }

        void loadParameters()
        {
            cmbPort.DataSource = SerialPort.GetPortNames();
            cmbPort.Text = Properties.Settings.Default.Port;
            txtBaud.Text = Properties.Settings.Default.Baud;
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
                txtBaud.Enabled = true;
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
                    sp.BaudRate = Convert.ToInt32(txtBaud.Text);
                    sp.StopBits = StopBits.One;
                    sp.Parity = Parity.None;
                    sp.DataBits = 8;
                    sp.NewLine = "\r\n";
                    sp.Open();
                    btnConnect.Text = "DisConnect";
                    btnDTR.Text = "Reset [DTR:" + sp.DtrEnable.ToString() + "]";
                    txtBaud.Enabled = false;
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
        static int counter = 0, bps = 0;
        private void tmrDataPoll_Tick(object sender, EventArgs e)
        {
            
            if (sp.IsOpen)
            {
                string str = sp.ReadExisting();
                rtbPort.AppendText(str);
                if (str.Length > 0) rtbPort.ScrollToCaret();
                if (counter++ >= 10)
                {
                    counter = 0;
                    this.Text = "Robot Remote Computer Terminal: " + bps.ToString() + " Bytes/Sec";
                    bps = 0;
                }
                else
                    bps += str.Length;
                if (parseRxData)
                {
                    //string[] words = { "Kp:", "Ki:", "Kd:" };
                    //HighlightWords(words);
                    //string word = "Kp: ";
                    //int wordStartIndex = rtbPort.Find(word, RichTextBoxFinds.Reverse);
                    //if (wordStartIndex != -1)
                    //{
                    //    rtbPort.SelectionStart = wordStartIndex;
                    //    rtbPort.SelectionLength = word.Length;
                    //    rtbPort.SelectionBackColor = Color.Yellow;
                    //    txtKp.Text = rtbPort.Text.Substring(wordStartIndex + word.Length, 3);
                    //}
                    Regex regexKp = new Regex(@"Kp: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKp = regexKp.Match(rtbPort.Text);
                    Regex regexKi = new Regex(@"Ki: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKi = regexKi.Match(rtbPort.Text);
                    Regex regexKd = new Regex(@"Kd: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKd = regexKd.Match(rtbPort.Text);
                    Regex regexKv = new Regex(@"Kv: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKv = regexKv.Match(rtbPort.Text);
                    Regex regexKw = new Regex(@"Kw: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKw = regexKw.Match(rtbPort.Text);
                    Regex regexKwos = new Regex(@"Kwos: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKwos = regexKwos.Match(rtbPort.Text);
                    Regex regexKir = new Regex(@"Kir: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKir = regexKir.Match(rtbPort.Text);
                    Regex regexKusFront = new Regex(@"KusFront: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKusFront = regexKusFront.Match(rtbPort.Text);
                    Regex regexKusSide = new Regex(@"KusSide: \d{1,8}\.\d{1,8}", RegexOptions.RightToLeft);
                    Match matchKusSide = regexKusSide.Match(rtbPort.Text);
                    Regex regexVlSamples = new Regex(@"VlSamples: \d{1,3}", RegexOptions.RightToLeft);
                    Match matchVlSamples = regexVlSamples.Match(rtbPort.Text);
                    Regex regexIRSamples = new Regex(@"IRSamples: \d{1,3}", RegexOptions.RightToLeft);
                    Match matchIRSamples = regexIRSamples.Match(rtbPort.Text);
                    Regex regexUSSamples = new Regex(@"USSamples: \d{1,3}", RegexOptions.RightToLeft);
                    Match matchUSSamples = regexUSSamples.Match(rtbPort.Text);
                    Regex regexIRCalib = new Regex(@"IRCalib: \d{1,3},\d{1,3},\d{1,3},\d{1,3},\d{1,3}", RegexOptions.RightToLeft);
                    Match matchIRCalib = regexIRCalib.Match(rtbPort.Text);
                    if (matchIRCalib.Value.Length>0)
                    {
                        parseRxData = false;
                        //String temp = matchKp.Value + "\n" + matchKi.Value + "\n" + matchKd.Value + "\n" +
                        //                matchKv.Value + "\n" + matchKw.Value + "\n" + matchKwos.Value + "\n" +
                        //                matchKir.Value + "\n" + matchKusFront.Value + "\n" + matchKusSide.Value + "\n" +
                        //                matchVlSamples.Value + "\n" + matchIRSamples.Value + "\n" + matchUSSamples.Value + "\n" +
                        //                matchIRCalib.Value;
                        //MessageBox.Show(temp);
                        //rtbPort.AppendText(temp);
                        txtKp.Text = matchKp.Value.Substring(4);
                        txtKi.Text = matchKi.Value.Substring(4);
                        txtKd.Text = matchKd.Value.Substring(4);
                        txtKv.Text = matchKv.Value.Substring(4);
                        txtKw.Text = matchKw.Value.Substring(4);
                        txtKwos.Text = matchKwos.Value.Substring(6);
                        txtIRThreshold.Text = matchKir.Value.Substring(5);
                        txtUSFrontThreshold.Text = matchKusFront.Value.Substring(10);
                        txtUSSideThreshold.Text = matchKusSide.Value.Substring(9);
                        txtVSamples.Text = matchVlSamples.Value.Substring(11);
                        txtIRSamples.Text = matchIRSamples.Value.Substring(11);
                        txtUSSamples.Text = matchUSSamples.Value.Substring(11);
                        String[] strs = matchIRCalib.Value.Substring(9).Split(',');
                        txtIRCalibLeft.Text = strs[0];
                        txtIRCalibMiddleLeft.Text = strs[1];
                        txtIRCalibMiddle.Text = strs[2];
                        txtIRCalibMiddleRight.Text = strs[3];
                        txtIRCalibRight.Text = strs[4];
                    }
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
