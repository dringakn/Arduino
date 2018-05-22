namespace Robot_Control_Terminal
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tmrDataPoll = new System.Windows.Forms.Timer(this.components);
            this.sp = new System.IO.Ports.SerialPort(this.components);
            this.btnClearTerminal = new System.Windows.Forms.Button();
            this.btnConnect = new System.Windows.Forms.Button();
            this.cmbPort = new System.Windows.Forms.ComboBox();
            this.rtbPort = new System.Windows.Forms.RichTextBox();
            this.txtCommand = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnReadPID = new System.Windows.Forms.Button();
            this.btnReadEncoder = new System.Windows.Forms.Button();
            this.btnReadAllSensors = new System.Windows.Forms.Button();
            this.btnReadInfrared = new System.Windows.Forms.Button();
            this.btnReadUltrasonic = new System.Windows.Forms.Button();
            this.btnReadOdometry = new System.Windows.Forms.Button();
            this.btnHelp = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btnResetOdometry = new System.Windows.Forms.Button();
            this.btnResetRobot = new System.Windows.Forms.Button();
            this.btnResetIR = new System.Windows.Forms.Button();
            this.btnMotorStop = new System.Windows.Forms.Button();
            this.btnSetPID = new System.Windows.Forms.Button();
            this.btnSetOdometricConstants = new System.Windows.Forms.Button();
            this.btnSetSamples = new System.Windows.Forms.Button();
            this.btnSetThreshold = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.txtIRThreshold = new System.Windows.Forms.TextBox();
            this.txtUSSideThreshold = new System.Windows.Forms.TextBox();
            this.txtUSFrontThreshold = new System.Windows.Forms.TextBox();
            this.txtKd = new System.Windows.Forms.TextBox();
            this.txtKi = new System.Windows.Forms.TextBox();
            this.txtKp = new System.Windows.Forms.TextBox();
            this.txtKwos = new System.Windows.Forms.TextBox();
            this.txtKw = new System.Windows.Forms.TextBox();
            this.txtKv = new System.Windows.Forms.TextBox();
            this.txtUSSamples = new System.Windows.Forms.TextBox();
            this.txtIRSamples = new System.Windows.Forms.TextBox();
            this.txtVSamples = new System.Windows.Forms.TextBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtTime = new System.Windows.Forms.TextBox();
            this.txtW = new System.Windows.Forms.TextBox();
            this.txtV = new System.Windows.Forms.TextBox();
            this.btnMotorOpenLoop = new System.Windows.Forms.Button();
            this.btnMotorCloseLoop = new System.Windows.Forms.Button();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.txtIRCalibRight = new System.Windows.Forms.TextBox();
            this.txtIRCalibMiddleRight = new System.Windows.Forms.TextBox();
            this.txtIRCalibMiddle = new System.Windows.Forms.TextBox();
            this.txtIRCalibMiddleLeft = new System.Windows.Forms.TextBox();
            this.txtIRCalibLeft = new System.Windows.Forms.TextBox();
            this.btnDTR = new System.Windows.Forms.Button();
            this.txtBaud = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // tmrDataPoll
            // 
            this.tmrDataPoll.Enabled = true;
            this.tmrDataPoll.Tick += new System.EventHandler(this.tmrDataPoll_Tick);
            // 
            // btnClearTerminal
            // 
            this.btnClearTerminal.Location = new System.Drawing.Point(861, 40);
            this.btnClearTerminal.Name = "btnClearTerminal";
            this.btnClearTerminal.Size = new System.Drawing.Size(66, 23);
            this.btnClearTerminal.TabIndex = 4;
            this.btnClearTerminal.Text = "Clear Term";
            this.btnClearTerminal.UseVisualStyleBackColor = true;
            this.btnClearTerminal.Click += new System.EventHandler(this.btnClearTerminal_Click);
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(861, 12);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(66, 23);
            this.btnConnect.TabIndex = 1;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // cmbPort
            // 
            this.cmbPort.FormattingEnabled = true;
            this.cmbPort.Location = new System.Drawing.Point(724, 14);
            this.cmbPort.Name = "cmbPort";
            this.cmbPort.Size = new System.Drawing.Size(58, 21);
            this.cmbPort.TabIndex = 0;
            this.cmbPort.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.cmbPort_MouseDoubleClick);
            // 
            // rtbPort
            // 
            this.rtbPort.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rtbPort.Location = new System.Drawing.Point(12, 12);
            this.rtbPort.Name = "rtbPort";
            this.rtbPort.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedBoth;
            this.rtbPort.Size = new System.Drawing.Size(706, 413);
            this.rtbPort.TabIndex = 3;
            this.rtbPort.Text = "";
            this.rtbPort.WordWrap = false;
            // 
            // txtCommand
            // 
            this.txtCommand.Location = new System.Drawing.Point(724, 70);
            this.txtCommand.Name = "txtCommand";
            this.txtCommand.Size = new System.Drawing.Size(316, 20);
            this.txtCommand.TabIndex = 5;
            this.txtCommand.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtCommand_PreviewKeyDown);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnReadPID);
            this.groupBox1.Controls.Add(this.btnReadEncoder);
            this.groupBox1.Controls.Add(this.btnReadAllSensors);
            this.groupBox1.Controls.Add(this.btnReadInfrared);
            this.groupBox1.Controls.Add(this.btnReadUltrasonic);
            this.groupBox1.Controls.Add(this.btnReadOdometry);
            this.groupBox1.Location = new System.Drawing.Point(948, 209);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(92, 216);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Read";
            // 
            // btnReadPID
            // 
            this.btnReadPID.Location = new System.Drawing.Point(6, 134);
            this.btnReadPID.Name = "btnReadPID";
            this.btnReadPID.Size = new System.Drawing.Size(75, 23);
            this.btnReadPID.TabIndex = 4;
            this.btnReadPID.Text = "PID";
            this.btnReadPID.UseVisualStyleBackColor = true;
            this.btnReadPID.Click += new System.EventHandler(this.btnReadPID_Click);
            // 
            // btnReadEncoder
            // 
            this.btnReadEncoder.Location = new System.Drawing.Point(6, 105);
            this.btnReadEncoder.Name = "btnReadEncoder";
            this.btnReadEncoder.Size = new System.Drawing.Size(75, 23);
            this.btnReadEncoder.TabIndex = 3;
            this.btnReadEncoder.Text = "Encoder";
            this.btnReadEncoder.UseVisualStyleBackColor = true;
            this.btnReadEncoder.Click += new System.EventHandler(this.btnReadEncoder_Click);
            // 
            // btnReadAllSensors
            // 
            this.btnReadAllSensors.Location = new System.Drawing.Point(6, 163);
            this.btnReadAllSensors.Name = "btnReadAllSensors";
            this.btnReadAllSensors.Size = new System.Drawing.Size(75, 47);
            this.btnReadAllSensors.TabIndex = 5;
            this.btnReadAllSensors.Text = "All Sensors";
            this.btnReadAllSensors.UseVisualStyleBackColor = true;
            this.btnReadAllSensors.Click += new System.EventHandler(this.btnReadAllSensors_Click);
            // 
            // btnReadInfrared
            // 
            this.btnReadInfrared.Location = new System.Drawing.Point(6, 76);
            this.btnReadInfrared.Name = "btnReadInfrared";
            this.btnReadInfrared.Size = new System.Drawing.Size(75, 23);
            this.btnReadInfrared.TabIndex = 2;
            this.btnReadInfrared.Text = "Infrared";
            this.btnReadInfrared.UseVisualStyleBackColor = true;
            this.btnReadInfrared.Click += new System.EventHandler(this.btnReadInfrared_Click);
            // 
            // btnReadUltrasonic
            // 
            this.btnReadUltrasonic.Location = new System.Drawing.Point(6, 47);
            this.btnReadUltrasonic.Name = "btnReadUltrasonic";
            this.btnReadUltrasonic.Size = new System.Drawing.Size(75, 23);
            this.btnReadUltrasonic.TabIndex = 1;
            this.btnReadUltrasonic.Text = "Ultrasonic";
            this.btnReadUltrasonic.UseVisualStyleBackColor = true;
            this.btnReadUltrasonic.Click += new System.EventHandler(this.btnReadUltrasonic_Click);
            // 
            // btnReadOdometry
            // 
            this.btnReadOdometry.Location = new System.Drawing.Point(6, 18);
            this.btnReadOdometry.Name = "btnReadOdometry";
            this.btnReadOdometry.Size = new System.Drawing.Size(75, 23);
            this.btnReadOdometry.TabIndex = 0;
            this.btnReadOdometry.Text = "Odometry";
            this.btnReadOdometry.UseVisualStyleBackColor = true;
            this.btnReadOdometry.Click += new System.EventHandler(this.btnReadOdometry_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.Location = new System.Drawing.Point(933, 12);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(107, 23);
            this.btnHelp.TabIndex = 2;
            this.btnHelp.Text = "Talk to me...";
            this.btnHelp.UseVisualStyleBackColor = true;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(725, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(133, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Data [Press enter to send]:";
            // 
            // btnResetOdometry
            // 
            this.btnResetOdometry.Location = new System.Drawing.Point(6, 19);
            this.btnResetOdometry.Name = "btnResetOdometry";
            this.btnResetOdometry.Size = new System.Drawing.Size(88, 23);
            this.btnResetOdometry.TabIndex = 0;
            this.btnResetOdometry.Text = "Reset Odom";
            this.btnResetOdometry.UseVisualStyleBackColor = true;
            this.btnResetOdometry.Click += new System.EventHandler(this.btnResetOdometry_Click);
            // 
            // btnResetRobot
            // 
            this.btnResetRobot.Location = new System.Drawing.Point(6, 48);
            this.btnResetRobot.Name = "btnResetRobot";
            this.btnResetRobot.Size = new System.Drawing.Size(88, 23);
            this.btnResetRobot.TabIndex = 1;
            this.btnResetRobot.Text = "Reset Robot";
            this.btnResetRobot.UseVisualStyleBackColor = true;
            this.btnResetRobot.Click += new System.EventHandler(this.btnResetRobot_Click);
            // 
            // btnResetIR
            // 
            this.btnResetIR.Location = new System.Drawing.Point(6, 77);
            this.btnResetIR.Name = "btnResetIR";
            this.btnResetIR.Size = new System.Drawing.Size(88, 23);
            this.btnResetIR.TabIndex = 2;
            this.btnResetIR.Text = "Calibrate IR";
            this.btnResetIR.UseVisualStyleBackColor = true;
            this.btnResetIR.Click += new System.EventHandler(this.btnResetIR_Click);
            // 
            // btnMotorStop
            // 
            this.btnMotorStop.Location = new System.Drawing.Point(9, 19);
            this.btnMotorStop.Name = "btnMotorStop";
            this.btnMotorStop.Size = new System.Drawing.Size(94, 23);
            this.btnMotorStop.TabIndex = 0;
            this.btnMotorStop.Text = "Stop";
            this.btnMotorStop.UseVisualStyleBackColor = true;
            this.btnMotorStop.Click += new System.EventHandler(this.btnMotorStop_Click);
            // 
            // btnSetPID
            // 
            this.btnSetPID.Location = new System.Drawing.Point(8, 106);
            this.btnSetPID.Name = "btnSetPID";
            this.btnSetPID.Size = new System.Drawing.Size(92, 23);
            this.btnSetPID.TabIndex = 12;
            this.btnSetPID.Text = "Motors PID";
            this.btnSetPID.UseVisualStyleBackColor = true;
            this.btnSetPID.Click += new System.EventHandler(this.btnSetPID_Click);
            // 
            // btnSetOdometricConstants
            // 
            this.btnSetOdometricConstants.Location = new System.Drawing.Point(8, 77);
            this.btnSetOdometricConstants.Name = "btnSetOdometricConstants";
            this.btnSetOdometricConstants.Size = new System.Drawing.Size(94, 23);
            this.btnSetOdometricConstants.TabIndex = 8;
            this.btnSetOdometricConstants.Text = "Odom. Constant";
            this.btnSetOdometricConstants.UseVisualStyleBackColor = true;
            this.btnSetOdometricConstants.Click += new System.EventHandler(this.btnSetOdometricConstants_Click);
            // 
            // btnSetSamples
            // 
            this.btnSetSamples.Location = new System.Drawing.Point(6, 19);
            this.btnSetSamples.Name = "btnSetSamples";
            this.btnSetSamples.Size = new System.Drawing.Size(94, 23);
            this.btnSetSamples.TabIndex = 0;
            this.btnSetSamples.Text = "Filtering Samples";
            this.btnSetSamples.UseVisualStyleBackColor = true;
            this.btnSetSamples.Click += new System.EventHandler(this.btnSetSamples_Click);
            // 
            // btnSetThreshold
            // 
            this.btnSetThreshold.Location = new System.Drawing.Point(6, 48);
            this.btnSetThreshold.Name = "btnSetThreshold";
            this.btnSetThreshold.Size = new System.Drawing.Size(94, 23);
            this.btnSetThreshold.TabIndex = 4;
            this.btnSetThreshold.Text = "Dist. Threshold";
            this.btnSetThreshold.UseVisualStyleBackColor = true;
            this.btnSetThreshold.Click += new System.EventHandler(this.btnSetThreshold_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnResetOdometry);
            this.groupBox2.Controls.Add(this.btnResetRobot);
            this.groupBox2.Controls.Add(this.btnResetIR);
            this.groupBox2.Location = new System.Drawing.Point(728, 93);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(100, 110);
            this.groupBox2.TabIndex = 16;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Reset";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.txtIRThreshold);
            this.groupBox3.Controls.Add(this.txtUSSideThreshold);
            this.groupBox3.Controls.Add(this.txtUSFrontThreshold);
            this.groupBox3.Controls.Add(this.txtKd);
            this.groupBox3.Controls.Add(this.txtKi);
            this.groupBox3.Controls.Add(this.txtKp);
            this.groupBox3.Controls.Add(this.txtKwos);
            this.groupBox3.Controls.Add(this.txtKw);
            this.groupBox3.Controls.Add(this.txtKv);
            this.groupBox3.Controls.Add(this.txtUSSamples);
            this.groupBox3.Controls.Add(this.txtIRSamples);
            this.groupBox3.Controls.Add(this.txtVSamples);
            this.groupBox3.Controls.Add(this.btnSetSamples);
            this.groupBox3.Controls.Add(this.btnSetThreshold);
            this.groupBox3.Controls.Add(this.btnSetPID);
            this.groupBox3.Controls.Add(this.btnSetOdometricConstants);
            this.groupBox3.Location = new System.Drawing.Point(726, 209);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(215, 157);
            this.groupBox3.TabIndex = 17;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Set";
            // 
            // txtIRThreshold
            // 
            this.txtIRThreshold.Location = new System.Drawing.Point(106, 50);
            this.txtIRThreshold.Name = "txtIRThreshold";
            this.txtIRThreshold.Size = new System.Drawing.Size(29, 20);
            this.txtIRThreshold.TabIndex = 5;
            this.txtIRThreshold.Text = "200";
            // 
            // txtUSSideThreshold
            // 
            this.txtUSSideThreshold.Location = new System.Drawing.Point(172, 50);
            this.txtUSSideThreshold.Name = "txtUSSideThreshold";
            this.txtUSSideThreshold.Size = new System.Drawing.Size(29, 20);
            this.txtUSSideThreshold.TabIndex = 7;
            this.txtUSSideThreshold.Text = "20";
            // 
            // txtUSFrontThreshold
            // 
            this.txtUSFrontThreshold.Location = new System.Drawing.Point(139, 50);
            this.txtUSFrontThreshold.Name = "txtUSFrontThreshold";
            this.txtUSFrontThreshold.Size = new System.Drawing.Size(29, 20);
            this.txtUSFrontThreshold.TabIndex = 6;
            this.txtUSFrontThreshold.Text = "25";
            // 
            // txtKd
            // 
            this.txtKd.Location = new System.Drawing.Point(174, 106);
            this.txtKd.Name = "txtKd";
            this.txtKd.Size = new System.Drawing.Size(29, 20);
            this.txtKd.TabIndex = 15;
            this.txtKd.Text = "1";
            // 
            // txtKi
            // 
            this.txtKi.Location = new System.Drawing.Point(139, 106);
            this.txtKi.Name = "txtKi";
            this.txtKi.Size = new System.Drawing.Size(29, 20);
            this.txtKi.TabIndex = 14;
            this.txtKi.Text = "20";
            // 
            // txtKp
            // 
            this.txtKp.Location = new System.Drawing.Point(104, 106);
            this.txtKp.Name = "txtKp";
            this.txtKp.Size = new System.Drawing.Size(29, 20);
            this.txtKp.TabIndex = 13;
            this.txtKp.Text = "20";
            // 
            // txtKwos
            // 
            this.txtKwos.Location = new System.Drawing.Point(174, 80);
            this.txtKwos.Name = "txtKwos";
            this.txtKwos.Size = new System.Drawing.Size(29, 20);
            this.txtKwos.TabIndex = 11;
            this.txtKwos.Text = "0";
            // 
            // txtKw
            // 
            this.txtKw.Location = new System.Drawing.Point(139, 80);
            this.txtKw.Name = "txtKw";
            this.txtKw.Size = new System.Drawing.Size(29, 20);
            this.txtKw.TabIndex = 10;
            this.txtKw.Text = "1";
            // 
            // txtKv
            // 
            this.txtKv.Location = new System.Drawing.Point(104, 79);
            this.txtKv.Name = "txtKv";
            this.txtKv.Size = new System.Drawing.Size(29, 20);
            this.txtKv.TabIndex = 9;
            this.txtKv.Text = "1";
            // 
            // txtUSSamples
            // 
            this.txtUSSamples.Location = new System.Drawing.Point(174, 22);
            this.txtUSSamples.Name = "txtUSSamples";
            this.txtUSSamples.Size = new System.Drawing.Size(27, 20);
            this.txtUSSamples.TabIndex = 3;
            this.txtUSSamples.Text = "3";
            // 
            // txtIRSamples
            // 
            this.txtIRSamples.Location = new System.Drawing.Point(141, 22);
            this.txtIRSamples.Name = "txtIRSamples";
            this.txtIRSamples.Size = new System.Drawing.Size(27, 20);
            this.txtIRSamples.TabIndex = 2;
            this.txtIRSamples.Text = "5";
            // 
            // txtVSamples
            // 
            this.txtVSamples.Location = new System.Drawing.Point(106, 21);
            this.txtVSamples.Name = "txtVSamples";
            this.txtVSamples.Size = new System.Drawing.Size(29, 20);
            this.txtVSamples.TabIndex = 1;
            this.txtVSamples.Text = "10";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.Controls.Add(this.txtTime);
            this.groupBox4.Controls.Add(this.txtW);
            this.groupBox4.Controls.Add(this.txtV);
            this.groupBox4.Controls.Add(this.btnMotorOpenLoop);
            this.groupBox4.Controls.Add(this.btnMotorCloseLoop);
            this.groupBox4.Controls.Add(this.btnMotorStop);
            this.groupBox4.Location = new System.Drawing.Point(840, 96);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(200, 108);
            this.groupBox4.TabIndex = 18;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Motors";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(103, 77);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(30, 13);
            this.label4.TabIndex = 19;
            this.label4.Text = "Time";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(103, 51);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 13);
            this.label3.TabIndex = 19;
            this.label3.Text = "VR/W";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(103, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 13);
            this.label2.TabIndex = 19;
            this.label2.Text = "VL/V";
            // 
            // txtTime
            // 
            this.txtTime.Location = new System.Drawing.Point(141, 74);
            this.txtTime.Name = "txtTime";
            this.txtTime.Size = new System.Drawing.Size(53, 20);
            this.txtTime.TabIndex = 5;
            this.txtTime.Text = "-1";
            // 
            // txtW
            // 
            this.txtW.Location = new System.Drawing.Point(141, 48);
            this.txtW.Name = "txtW";
            this.txtW.Size = new System.Drawing.Size(53, 20);
            this.txtW.TabIndex = 3;
            this.txtW.Text = "0";
            // 
            // txtV
            // 
            this.txtV.Location = new System.Drawing.Point(141, 19);
            this.txtV.Name = "txtV";
            this.txtV.Size = new System.Drawing.Size(53, 20);
            this.txtV.TabIndex = 1;
            this.txtV.Text = "10";
            // 
            // btnMotorOpenLoop
            // 
            this.btnMotorOpenLoop.Location = new System.Drawing.Point(9, 77);
            this.btnMotorOpenLoop.Name = "btnMotorOpenLoop";
            this.btnMotorOpenLoop.Size = new System.Drawing.Size(94, 23);
            this.btnMotorOpenLoop.TabIndex = 4;
            this.btnMotorOpenLoop.Text = "Open Loop";
            this.btnMotorOpenLoop.UseVisualStyleBackColor = true;
            this.btnMotorOpenLoop.Click += new System.EventHandler(this.btnMotorOpenLoop_Click);
            // 
            // btnMotorCloseLoop
            // 
            this.btnMotorCloseLoop.Location = new System.Drawing.Point(9, 48);
            this.btnMotorCloseLoop.Name = "btnMotorCloseLoop";
            this.btnMotorCloseLoop.Size = new System.Drawing.Size(94, 23);
            this.btnMotorCloseLoop.TabIndex = 2;
            this.btnMotorCloseLoop.Text = "Close Loop";
            this.btnMotorCloseLoop.UseVisualStyleBackColor = true;
            this.btnMotorCloseLoop.Click += new System.EventHandler(this.btnMotorCloseLoop_Click);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.txtIRCalibRight);
            this.groupBox5.Controls.Add(this.txtIRCalibMiddleRight);
            this.groupBox5.Controls.Add(this.txtIRCalibMiddle);
            this.groupBox5.Controls.Add(this.txtIRCalibMiddleLeft);
            this.groupBox5.Controls.Add(this.txtIRCalibLeft);
            this.groupBox5.Location = new System.Drawing.Point(734, 372);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(207, 42);
            this.groupBox5.TabIndex = 19;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "IR Calib";
            // 
            // txtIRCalibRight
            // 
            this.txtIRCalibRight.Location = new System.Drawing.Point(146, 16);
            this.txtIRCalibRight.Name = "txtIRCalibRight";
            this.txtIRCalibRight.Size = new System.Drawing.Size(29, 20);
            this.txtIRCalibRight.TabIndex = 4;
            this.txtIRCalibRight.Text = "0";
            // 
            // txtIRCalibMiddleRight
            // 
            this.txtIRCalibMiddleRight.Location = new System.Drawing.Point(111, 16);
            this.txtIRCalibMiddleRight.Name = "txtIRCalibMiddleRight";
            this.txtIRCalibMiddleRight.Size = new System.Drawing.Size(29, 20);
            this.txtIRCalibMiddleRight.TabIndex = 3;
            this.txtIRCalibMiddleRight.Text = "0";
            // 
            // txtIRCalibMiddle
            // 
            this.txtIRCalibMiddle.Location = new System.Drawing.Point(76, 16);
            this.txtIRCalibMiddle.Name = "txtIRCalibMiddle";
            this.txtIRCalibMiddle.Size = new System.Drawing.Size(29, 20);
            this.txtIRCalibMiddle.TabIndex = 2;
            this.txtIRCalibMiddle.Text = "0";
            // 
            // txtIRCalibMiddleLeft
            // 
            this.txtIRCalibMiddleLeft.Location = new System.Drawing.Point(41, 16);
            this.txtIRCalibMiddleLeft.Name = "txtIRCalibMiddleLeft";
            this.txtIRCalibMiddleLeft.Size = new System.Drawing.Size(29, 20);
            this.txtIRCalibMiddleLeft.TabIndex = 1;
            this.txtIRCalibMiddleLeft.Text = "0";
            // 
            // txtIRCalibLeft
            // 
            this.txtIRCalibLeft.Location = new System.Drawing.Point(6, 16);
            this.txtIRCalibLeft.Name = "txtIRCalibLeft";
            this.txtIRCalibLeft.Size = new System.Drawing.Size(29, 20);
            this.txtIRCalibLeft.TabIndex = 0;
            this.txtIRCalibLeft.Text = "0";
            // 
            // btnDTR
            // 
            this.btnDTR.Location = new System.Drawing.Point(933, 40);
            this.btnDTR.Name = "btnDTR";
            this.btnDTR.Size = new System.Drawing.Size(107, 23);
            this.btnDTR.TabIndex = 3;
            this.btnDTR.Text = "DTR";
            this.btnDTR.UseVisualStyleBackColor = true;
            this.btnDTR.Click += new System.EventHandler(this.btnDTR_Click);
            // 
            // txtBaud
            // 
            this.txtBaud.Location = new System.Drawing.Point(788, 14);
            this.txtBaud.Name = "txtBaud";
            this.txtBaud.Size = new System.Drawing.Size(67, 20);
            this.txtBaud.TabIndex = 20;
            this.txtBaud.Text = "115200";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1051, 435);
            this.Controls.Add(this.txtBaud);
            this.Controls.Add(this.btnDTR);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.txtCommand);
            this.Controls.Add(this.rtbPort);
            this.Controls.Add(this.cmbPort);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnClearTerminal);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Robot Remote Computer Terminal";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer tmrDataPoll;
        private System.IO.Ports.SerialPort sp;
        private System.Windows.Forms.Button btnClearTerminal;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.ComboBox cmbPort;
        private System.Windows.Forms.RichTextBox rtbPort;
        private System.Windows.Forms.TextBox txtCommand;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnReadAllSensors;
        private System.Windows.Forms.Button btnReadInfrared;
        private System.Windows.Forms.Button btnReadUltrasonic;
        private System.Windows.Forms.Button btnReadOdometry;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnReadPID;
        private System.Windows.Forms.Button btnReadEncoder;
        private System.Windows.Forms.Button btnResetOdometry;
        private System.Windows.Forms.Button btnResetRobot;
        private System.Windows.Forms.Button btnResetIR;
        private System.Windows.Forms.Button btnMotorStop;
        private System.Windows.Forms.Button btnSetPID;
        private System.Windows.Forms.Button btnSetOdometricConstants;
        private System.Windows.Forms.Button btnSetSamples;
        private System.Windows.Forms.Button btnSetThreshold;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtTime;
        private System.Windows.Forms.TextBox txtW;
        private System.Windows.Forms.TextBox txtV;
        private System.Windows.Forms.Button btnMotorOpenLoop;
        private System.Windows.Forms.Button btnMotorCloseLoop;
        private System.Windows.Forms.TextBox txtKd;
        private System.Windows.Forms.TextBox txtKi;
        private System.Windows.Forms.TextBox txtKp;
        private System.Windows.Forms.TextBox txtKwos;
        private System.Windows.Forms.TextBox txtKw;
        private System.Windows.Forms.TextBox txtKv;
        private System.Windows.Forms.TextBox txtUSSamples;
        private System.Windows.Forms.TextBox txtVSamples;
        private System.Windows.Forms.TextBox txtIRThreshold;
        private System.Windows.Forms.TextBox txtUSSideThreshold;
        private System.Windows.Forms.TextBox txtUSFrontThreshold;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TextBox txtIRCalibRight;
        private System.Windows.Forms.TextBox txtIRCalibMiddleRight;
        private System.Windows.Forms.TextBox txtIRCalibMiddle;
        private System.Windows.Forms.TextBox txtIRCalibMiddleLeft;
        private System.Windows.Forms.TextBox txtIRCalibLeft;
        private System.Windows.Forms.Button btnDTR;
        private System.Windows.Forms.TextBox txtIRSamples;
        private System.Windows.Forms.TextBox txtBaud;
    }
}

