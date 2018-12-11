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
            this.lblTime = new System.Windows.Forms.Label();
            this.lblW = new System.Windows.Forms.Label();
            this.lblV = new System.Windows.Forms.Label();
            this.txtTime = new System.Windows.Forms.TextBox();
            this.txtW = new System.Windows.Forms.TextBox();
            this.txtV = new System.Windows.Forms.TextBox();
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
            // sp
            // 
            this.sp.BaudRate = 115200;
            // 
            // btnClearTerminal
            // 
            this.btnClearTerminal.Location = new System.Drawing.Point(904, 49);
            this.btnClearTerminal.Margin = new System.Windows.Forms.Padding(4);
            this.btnClearTerminal.Name = "btnClearTerminal";
            this.btnClearTerminal.Size = new System.Drawing.Size(117, 28);
            this.btnClearTerminal.TabIndex = 4;
            this.btnClearTerminal.Text = "Clear Terminal";
            this.btnClearTerminal.UseVisualStyleBackColor = true;
            this.btnClearTerminal.Click += new System.EventHandler(this.btnClearTerminal_Click);
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(904, 15);
            this.btnConnect.Margin = new System.Windows.Forms.Padding(4);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(117, 28);
            this.btnConnect.TabIndex = 1;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // cmbPort
            // 
            this.cmbPort.FormattingEnabled = true;
            this.cmbPort.Location = new System.Drawing.Point(641, 17);
            this.cmbPort.Margin = new System.Windows.Forms.Padding(4);
            this.cmbPort.Name = "cmbPort";
            this.cmbPort.Size = new System.Drawing.Size(143, 24);
            this.cmbPort.TabIndex = 0;
            this.cmbPort.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.cmbPort_MouseDoubleClick);
            // 
            // rtbPort
            // 
            this.rtbPort.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rtbPort.Location = new System.Drawing.Point(16, 15);
            this.rtbPort.Margin = new System.Windows.Forms.Padding(4);
            this.rtbPort.Name = "rtbPort";
            this.rtbPort.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedBoth;
            this.rtbPort.Size = new System.Drawing.Size(601, 507);
            this.rtbPort.TabIndex = 3;
            this.rtbPort.Text = "";
            this.rtbPort.WordWrap = false;
            // 
            // txtCommand
            // 
            this.txtCommand.Location = new System.Drawing.Point(641, 86);
            this.txtCommand.Margin = new System.Windows.Forms.Padding(4);
            this.txtCommand.Name = "txtCommand";
            this.txtCommand.Size = new System.Drawing.Size(557, 22);
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
            this.groupBox1.Location = new System.Drawing.Point(1067, 257);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(131, 266);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Read Sensors";
            // 
            // btnReadPID
            // 
            this.btnReadPID.Location = new System.Drawing.Point(8, 165);
            this.btnReadPID.Margin = new System.Windows.Forms.Padding(4);
            this.btnReadPID.Name = "btnReadPID";
            this.btnReadPID.Size = new System.Drawing.Size(100, 28);
            this.btnReadPID.TabIndex = 4;
            this.btnReadPID.Text = "Control";
            this.btnReadPID.UseVisualStyleBackColor = true;
            this.btnReadPID.Click += new System.EventHandler(this.btnReadPID_Click);
            // 
            // btnReadEncoder
            // 
            this.btnReadEncoder.Location = new System.Drawing.Point(8, 129);
            this.btnReadEncoder.Margin = new System.Windows.Forms.Padding(4);
            this.btnReadEncoder.Name = "btnReadEncoder";
            this.btnReadEncoder.Size = new System.Drawing.Size(100, 28);
            this.btnReadEncoder.TabIndex = 3;
            this.btnReadEncoder.Text = "Wheel Speed";
            this.btnReadEncoder.UseVisualStyleBackColor = true;
            this.btnReadEncoder.Click += new System.EventHandler(this.btnReadEncoder_Click);
            // 
            // btnReadAllSensors
            // 
            this.btnReadAllSensors.Location = new System.Drawing.Point(8, 201);
            this.btnReadAllSensors.Margin = new System.Windows.Forms.Padding(4);
            this.btnReadAllSensors.Name = "btnReadAllSensors";
            this.btnReadAllSensors.Size = new System.Drawing.Size(100, 58);
            this.btnReadAllSensors.TabIndex = 5;
            this.btnReadAllSensors.Text = "All Sensors";
            this.btnReadAllSensors.UseVisualStyleBackColor = true;
            this.btnReadAllSensors.Click += new System.EventHandler(this.btnReadAllSensors_Click);
            // 
            // btnReadInfrared
            // 
            this.btnReadInfrared.Location = new System.Drawing.Point(8, 94);
            this.btnReadInfrared.Margin = new System.Windows.Forms.Padding(4);
            this.btnReadInfrared.Name = "btnReadInfrared";
            this.btnReadInfrared.Size = new System.Drawing.Size(100, 28);
            this.btnReadInfrared.TabIndex = 2;
            this.btnReadInfrared.Text = "Line Detection";
            this.btnReadInfrared.UseVisualStyleBackColor = true;
            this.btnReadInfrared.Click += new System.EventHandler(this.btnReadInfrared_Click);
            // 
            // btnReadUltrasonic
            // 
            this.btnReadUltrasonic.Location = new System.Drawing.Point(8, 58);
            this.btnReadUltrasonic.Margin = new System.Windows.Forms.Padding(4);
            this.btnReadUltrasonic.Name = "btnReadUltrasonic";
            this.btnReadUltrasonic.Size = new System.Drawing.Size(100, 28);
            this.btnReadUltrasonic.TabIndex = 1;
            this.btnReadUltrasonic.Text = "Obstacle Avoidance";
            this.btnReadUltrasonic.UseVisualStyleBackColor = true;
            this.btnReadUltrasonic.Click += new System.EventHandler(this.btnReadUltrasonic_Click);
            // 
            // btnReadOdometry
            // 
            this.btnReadOdometry.Location = new System.Drawing.Point(8, 22);
            this.btnReadOdometry.Margin = new System.Windows.Forms.Padding(4);
            this.btnReadOdometry.Name = "btnReadOdometry";
            this.btnReadOdometry.Size = new System.Drawing.Size(100, 28);
            this.btnReadOdometry.TabIndex = 0;
            this.btnReadOdometry.Text = "Pose";
            this.btnReadOdometry.UseVisualStyleBackColor = true;
            this.btnReadOdometry.Click += new System.EventHandler(this.btnReadOdometry_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.Location = new System.Drawing.Point(1029, 15);
            this.btnHelp.Margin = new System.Windows.Forms.Padding(4);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(169, 28);
            this.btnHelp.TabIndex = 2;
            this.btnHelp.Text = "Talk to me...";
            this.btnHelp.UseVisualStyleBackColor = true;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(638, 60);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(178, 17);
            this.label1.TabIndex = 6;
            this.label1.Text = "Date [Press enter to send]:";
            // 
            // btnResetOdometry
            // 
            this.btnResetOdometry.Location = new System.Drawing.Point(8, 23);
            this.btnResetOdometry.Margin = new System.Windows.Forms.Padding(4);
            this.btnResetOdometry.Name = "btnResetOdometry";
            this.btnResetOdometry.Size = new System.Drawing.Size(205, 28);
            this.btnResetOdometry.TabIndex = 0;
            this.btnResetOdometry.Text = "Reset Robot Pose";
            this.btnResetOdometry.UseVisualStyleBackColor = true;
            this.btnResetOdometry.Click += new System.EventHandler(this.btnResetOdometry_Click);
            // 
            // btnResetRobot
            // 
            this.btnResetRobot.Location = new System.Drawing.Point(8, 59);
            this.btnResetRobot.Margin = new System.Windows.Forms.Padding(4);
            this.btnResetRobot.Name = "btnResetRobot";
            this.btnResetRobot.Size = new System.Drawing.Size(205, 28);
            this.btnResetRobot.TabIndex = 1;
            this.btnResetRobot.Text = "Reset Robot Controller";
            this.btnResetRobot.UseVisualStyleBackColor = true;
            this.btnResetRobot.Click += new System.EventHandler(this.btnResetRobot_Click);
            // 
            // btnResetIR
            // 
            this.btnResetIR.Location = new System.Drawing.Point(8, 95);
            this.btnResetIR.Margin = new System.Windows.Forms.Padding(4);
            this.btnResetIR.Name = "btnResetIR";
            this.btnResetIR.Size = new System.Drawing.Size(205, 28);
            this.btnResetIR.TabIndex = 2;
            this.btnResetIR.Text = "Calibrate Line Color";
            this.btnResetIR.UseVisualStyleBackColor = true;
            this.btnResetIR.Click += new System.EventHandler(this.btnResetIR_Click);
            // 
            // btnMotorStop
            // 
            this.btnMotorStop.Location = new System.Drawing.Point(12, 23);
            this.btnMotorStop.Margin = new System.Windows.Forms.Padding(4);
            this.btnMotorStop.Name = "btnMotorStop";
            this.btnMotorStop.Size = new System.Drawing.Size(144, 28);
            this.btnMotorStop.TabIndex = 0;
            this.btnMotorStop.Text = "Stop Robot";
            this.btnMotorStop.UseVisualStyleBackColor = true;
            this.btnMotorStop.Click += new System.EventHandler(this.btnMotorStop_Click);
            // 
            // btnSetPID
            // 
            this.btnSetPID.Location = new System.Drawing.Point(8, 130);
            this.btnSetPID.Margin = new System.Windows.Forms.Padding(4);
            this.btnSetPID.Name = "btnSetPID";
            this.btnSetPID.Size = new System.Drawing.Size(177, 28);
            this.btnSetPID.TabIndex = 12;
            this.btnSetPID.Text = "Update Motor Controller";
            this.btnSetPID.UseVisualStyleBackColor = true;
            this.btnSetPID.Click += new System.EventHandler(this.btnSetPID_Click);
            // 
            // btnSetOdometricConstants
            // 
            this.btnSetOdometricConstants.Location = new System.Drawing.Point(8, 95);
            this.btnSetOdometricConstants.Margin = new System.Windows.Forms.Padding(4);
            this.btnSetOdometricConstants.Name = "btnSetOdometricConstants";
            this.btnSetOdometricConstants.Size = new System.Drawing.Size(177, 28);
            this.btnSetOdometricConstants.TabIndex = 8;
            this.btnSetOdometricConstants.Text = "Update Motion Constants";
            this.btnSetOdometricConstants.UseVisualStyleBackColor = true;
            this.btnSetOdometricConstants.Click += new System.EventHandler(this.btnSetOdometricConstants_Click);
            // 
            // btnSetSamples
            // 
            this.btnSetSamples.Location = new System.Drawing.Point(8, 23);
            this.btnSetSamples.Margin = new System.Windows.Forms.Padding(4);
            this.btnSetSamples.Name = "btnSetSamples";
            this.btnSetSamples.Size = new System.Drawing.Size(177, 28);
            this.btnSetSamples.TabIndex = 0;
            this.btnSetSamples.Text = "Update Filtering";
            this.btnSetSamples.UseVisualStyleBackColor = true;
            this.btnSetSamples.Click += new System.EventHandler(this.btnSetSamples_Click);
            // 
            // btnSetThreshold
            // 
            this.btnSetThreshold.Location = new System.Drawing.Point(8, 59);
            this.btnSetThreshold.Margin = new System.Windows.Forms.Padding(4);
            this.btnSetThreshold.Name = "btnSetThreshold";
            this.btnSetThreshold.Size = new System.Drawing.Size(177, 28);
            this.btnSetThreshold.TabIndex = 4;
            this.btnSetThreshold.Text = "Update Threshold";
            this.btnSetThreshold.UseVisualStyleBackColor = true;
            this.btnSetThreshold.Click += new System.EventHandler(this.btnSetThreshold_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnResetOdometry);
            this.groupBox2.Controls.Add(this.btnResetRobot);
            this.groupBox2.Controls.Add(this.btnResetIR);
            this.groupBox2.Location = new System.Drawing.Point(633, 114);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox2.Size = new System.Drawing.Size(225, 135);
            this.groupBox2.TabIndex = 16;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Robot Commands";
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
            this.groupBox3.Location = new System.Drawing.Point(625, 257);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox3.Size = new System.Drawing.Size(434, 175);
            this.groupBox3.TabIndex = 17;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Change Settings";
            // 
            // txtIRThreshold
            // 
            this.txtIRThreshold.Location = new System.Drawing.Point(189, 62);
            this.txtIRThreshold.Margin = new System.Windows.Forms.Padding(4);
            this.txtIRThreshold.Name = "txtIRThreshold";
            this.txtIRThreshold.Size = new System.Drawing.Size(65, 22);
            this.txtIRThreshold.TabIndex = 5;
            this.txtIRThreshold.Text = "200";
            // 
            // txtUSSideThreshold
            // 
            this.txtUSSideThreshold.Location = new System.Drawing.Point(360, 62);
            this.txtUSSideThreshold.Margin = new System.Windows.Forms.Padding(4);
            this.txtUSSideThreshold.Name = "txtUSSideThreshold";
            this.txtUSSideThreshold.Size = new System.Drawing.Size(65, 22);
            this.txtUSSideThreshold.TabIndex = 7;
            this.txtUSSideThreshold.Text = "20";
            // 
            // txtUSFrontThreshold
            // 
            this.txtUSFrontThreshold.Location = new System.Drawing.Point(275, 62);
            this.txtUSFrontThreshold.Margin = new System.Windows.Forms.Padding(4);
            this.txtUSFrontThreshold.Name = "txtUSFrontThreshold";
            this.txtUSFrontThreshold.Size = new System.Drawing.Size(65, 22);
            this.txtUSFrontThreshold.TabIndex = 6;
            this.txtUSFrontThreshold.Text = "25";
            // 
            // txtKd
            // 
            this.txtKd.Location = new System.Drawing.Point(360, 130);
            this.txtKd.Margin = new System.Windows.Forms.Padding(4);
            this.txtKd.Name = "txtKd";
            this.txtKd.Size = new System.Drawing.Size(65, 22);
            this.txtKd.TabIndex = 15;
            this.txtKd.Text = "1";
            // 
            // txtKi
            // 
            this.txtKi.Location = new System.Drawing.Point(275, 130);
            this.txtKi.Margin = new System.Windows.Forms.Padding(4);
            this.txtKi.Name = "txtKi";
            this.txtKi.Size = new System.Drawing.Size(65, 22);
            this.txtKi.TabIndex = 14;
            this.txtKi.Text = "20";
            // 
            // txtKp
            // 
            this.txtKp.Location = new System.Drawing.Point(187, 130);
            this.txtKp.Margin = new System.Windows.Forms.Padding(4);
            this.txtKp.Name = "txtKp";
            this.txtKp.Size = new System.Drawing.Size(65, 22);
            this.txtKp.TabIndex = 13;
            this.txtKp.Text = "20";
            // 
            // txtKwos
            // 
            this.txtKwos.Location = new System.Drawing.Point(360, 98);
            this.txtKwos.Margin = new System.Windows.Forms.Padding(4);
            this.txtKwos.Name = "txtKwos";
            this.txtKwos.Size = new System.Drawing.Size(65, 22);
            this.txtKwos.TabIndex = 11;
            this.txtKwos.Text = "0";
            // 
            // txtKw
            // 
            this.txtKw.Location = new System.Drawing.Point(275, 98);
            this.txtKw.Margin = new System.Windows.Forms.Padding(4);
            this.txtKw.Name = "txtKw";
            this.txtKw.Size = new System.Drawing.Size(65, 22);
            this.txtKw.TabIndex = 10;
            this.txtKw.Text = "1";
            // 
            // txtKv
            // 
            this.txtKv.Location = new System.Drawing.Point(187, 97);
            this.txtKv.Margin = new System.Windows.Forms.Padding(4);
            this.txtKv.Name = "txtKv";
            this.txtKv.Size = new System.Drawing.Size(65, 22);
            this.txtKv.TabIndex = 9;
            this.txtKv.Text = "1";
            // 
            // txtUSSamples
            // 
            this.txtUSSamples.Location = new System.Drawing.Point(360, 27);
            this.txtUSSamples.Margin = new System.Windows.Forms.Padding(4);
            this.txtUSSamples.Name = "txtUSSamples";
            this.txtUSSamples.Size = new System.Drawing.Size(65, 22);
            this.txtUSSamples.TabIndex = 3;
            this.txtUSSamples.Text = "3";
            // 
            // txtIRSamples
            // 
            this.txtIRSamples.Location = new System.Drawing.Point(275, 27);
            this.txtIRSamples.Margin = new System.Windows.Forms.Padding(4);
            this.txtIRSamples.Name = "txtIRSamples";
            this.txtIRSamples.Size = new System.Drawing.Size(65, 22);
            this.txtIRSamples.TabIndex = 2;
            this.txtIRSamples.Text = "5";
            // 
            // txtVSamples
            // 
            this.txtVSamples.Location = new System.Drawing.Point(189, 26);
            this.txtVSamples.Margin = new System.Windows.Forms.Padding(4);
            this.txtVSamples.Name = "txtVSamples";
            this.txtVSamples.Size = new System.Drawing.Size(65, 22);
            this.txtVSamples.TabIndex = 1;
            this.txtVSamples.Text = "10";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.lblTime);
            this.groupBox4.Controls.Add(this.lblW);
            this.groupBox4.Controls.Add(this.lblV);
            this.groupBox4.Controls.Add(this.txtTime);
            this.groupBox4.Controls.Add(this.txtW);
            this.groupBox4.Controls.Add(this.txtV);
            this.groupBox4.Controls.Add(this.btnMotorCloseLoop);
            this.groupBox4.Controls.Add(this.btnMotorStop);
            this.groupBox4.Location = new System.Drawing.Point(865, 118);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox4.Size = new System.Drawing.Size(333, 133);
            this.groupBox4.TabIndex = 18;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Motion Commands";
            // 
            // lblTime
            // 
            this.lblTime.AutoSize = true;
            this.lblTime.Location = new System.Drawing.Point(163, 101);
            this.lblTime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(39, 17);
            this.lblTime.TabIndex = 19;
            this.lblTime.Text = "Time";
            // 
            // lblW
            // 
            this.lblW.AutoSize = true;
            this.lblW.Location = new System.Drawing.Point(163, 68);
            this.lblW.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblW.Name = "lblW";
            this.lblW.Size = new System.Drawing.Size(85, 17);
            this.lblW.TabIndex = 19;
            this.lblW.Text = "Angular Vel.";
            // 
            // lblV
            // 
            this.lblV.AutoSize = true;
            this.lblV.Location = new System.Drawing.Point(163, 27);
            this.lblV.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblV.Name = "lblV";
            this.lblV.Size = new System.Drawing.Size(76, 17);
            this.lblV.TabIndex = 19;
            this.lblV.Text = "Linear Vel.";
            // 
            // txtTime
            // 
            this.txtTime.Location = new System.Drawing.Point(249, 98);
            this.txtTime.Margin = new System.Windows.Forms.Padding(4);
            this.txtTime.Name = "txtTime";
            this.txtTime.Size = new System.Drawing.Size(69, 22);
            this.txtTime.TabIndex = 5;
            this.txtTime.Text = "-1";
            // 
            // txtW
            // 
            this.txtW.Location = new System.Drawing.Point(249, 63);
            this.txtW.Margin = new System.Windows.Forms.Padding(4);
            this.txtW.Name = "txtW";
            this.txtW.Size = new System.Drawing.Size(69, 22);
            this.txtW.TabIndex = 3;
            this.txtW.Text = "0";
            // 
            // txtV
            // 
            this.txtV.Location = new System.Drawing.Point(249, 24);
            this.txtV.Margin = new System.Windows.Forms.Padding(4);
            this.txtV.Name = "txtV";
            this.txtV.Size = new System.Drawing.Size(69, 22);
            this.txtV.TabIndex = 1;
            this.txtV.Text = "10";
            // 
            // btnMotorCloseLoop
            // 
            this.btnMotorCloseLoop.Location = new System.Drawing.Point(12, 59);
            this.btnMotorCloseLoop.Margin = new System.Windows.Forms.Padding(4);
            this.btnMotorCloseLoop.Name = "btnMotorCloseLoop";
            this.btnMotorCloseLoop.Size = new System.Drawing.Size(144, 61);
            this.btnMotorCloseLoop.TabIndex = 2;
            this.btnMotorCloseLoop.Text = "Move Robot";
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
            this.groupBox5.Location = new System.Drawing.Point(625, 458);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox5.Size = new System.Drawing.Size(434, 52);
            this.groupBox5.TabIndex = 19;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Calibrated Line Sensors Values";
            // 
            // txtIRCalibRight
            // 
            this.txtIRCalibRight.Location = new System.Drawing.Point(360, 22);
            this.txtIRCalibRight.Margin = new System.Windows.Forms.Padding(4);
            this.txtIRCalibRight.Name = "txtIRCalibRight";
            this.txtIRCalibRight.Size = new System.Drawing.Size(65, 22);
            this.txtIRCalibRight.TabIndex = 4;
            this.txtIRCalibRight.Text = "0";
            this.txtIRCalibRight.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtIRCalibMiddleRight
            // 
            this.txtIRCalibMiddleRight.Location = new System.Drawing.Point(272, 20);
            this.txtIRCalibMiddleRight.Margin = new System.Windows.Forms.Padding(4);
            this.txtIRCalibMiddleRight.Name = "txtIRCalibMiddleRight";
            this.txtIRCalibMiddleRight.Size = new System.Drawing.Size(65, 22);
            this.txtIRCalibMiddleRight.TabIndex = 3;
            this.txtIRCalibMiddleRight.Text = "0";
            this.txtIRCalibMiddleRight.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtIRCalibMiddle
            // 
            this.txtIRCalibMiddle.Location = new System.Drawing.Point(184, 20);
            this.txtIRCalibMiddle.Margin = new System.Windows.Forms.Padding(4);
            this.txtIRCalibMiddle.Name = "txtIRCalibMiddle";
            this.txtIRCalibMiddle.Size = new System.Drawing.Size(65, 22);
            this.txtIRCalibMiddle.TabIndex = 2;
            this.txtIRCalibMiddle.Text = "0";
            this.txtIRCalibMiddle.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtIRCalibMiddleLeft
            // 
            this.txtIRCalibMiddleLeft.Location = new System.Drawing.Point(96, 20);
            this.txtIRCalibMiddleLeft.Margin = new System.Windows.Forms.Padding(4);
            this.txtIRCalibMiddleLeft.Name = "txtIRCalibMiddleLeft";
            this.txtIRCalibMiddleLeft.Size = new System.Drawing.Size(65, 22);
            this.txtIRCalibMiddleLeft.TabIndex = 1;
            this.txtIRCalibMiddleLeft.Text = "0";
            this.txtIRCalibMiddleLeft.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtIRCalibLeft
            // 
            this.txtIRCalibLeft.Location = new System.Drawing.Point(8, 20);
            this.txtIRCalibLeft.Margin = new System.Windows.Forms.Padding(4);
            this.txtIRCalibLeft.Name = "txtIRCalibLeft";
            this.txtIRCalibLeft.Size = new System.Drawing.Size(65, 22);
            this.txtIRCalibLeft.TabIndex = 0;
            this.txtIRCalibLeft.Text = "0";
            this.txtIRCalibLeft.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // btnDTR
            // 
            this.btnDTR.Location = new System.Drawing.Point(1029, 49);
            this.btnDTR.Margin = new System.Windows.Forms.Padding(4);
            this.btnDTR.Name = "btnDTR";
            this.btnDTR.Size = new System.Drawing.Size(169, 28);
            this.btnDTR.TabIndex = 3;
            this.btnDTR.Text = "DTR";
            this.btnDTR.UseVisualStyleBackColor = true;
            this.btnDTR.Click += new System.EventHandler(this.btnDTR_Click);
            // 
            // txtBaud
            // 
            this.txtBaud.Location = new System.Drawing.Point(791, 18);
            this.txtBaud.Margin = new System.Windows.Forms.Padding(4);
            this.txtBaud.Name = "txtBaud";
            this.txtBaud.Size = new System.Drawing.Size(101, 22);
            this.txtBaud.TabIndex = 20;
            this.txtBaud.Text = "115200";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1213, 535);
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
            this.Margin = new System.Windows.Forms.Padding(4);
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
        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.Label lblW;
        private System.Windows.Forms.Label lblV;
        private System.Windows.Forms.TextBox txtTime;
        private System.Windows.Forms.TextBox txtW;
        private System.Windows.Forms.TextBox txtV;
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

