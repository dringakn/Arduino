namespace BluetoothTerminal
{
    partial class frmMain
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
            this.btnConnect = new System.Windows.Forms.Button();
            this.rtbPort1 = new System.Windows.Forms.RichTextBox();
            this.rtbPort2 = new System.Windows.Forms.RichTextBox();
            this.txtBaud = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.sp1 = new System.IO.Ports.SerialPort(this.components);
            this.sp2 = new System.IO.Ports.SerialPort(this.components);
            this.btnDTR = new System.Windows.Forms.Button();
            this.cmbPort1 = new System.Windows.Forms.ComboBox();
            this.cmbPort2 = new System.Windows.Forms.ComboBox();
            this.btnScanPorts = new System.Windows.Forms.Button();
            this.txtPort1Data1 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtPort1Data2 = new System.Windows.Forms.TextBox();
            this.txtPort1Data3 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.txtPort2Data1 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtPort2Data2 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtPort2Data3 = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.btnClearTerminal = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.txtPort1Data4 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.txtPort1Data5 = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.txtPort2Data4 = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.txtPort2Data5 = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(1037, 24);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(75, 21);
            this.btnConnect.TabIndex = 3;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // rtbPort1
            // 
            this.rtbPort1.Location = new System.Drawing.Point(12, 89);
            this.rtbPort1.Name = "rtbPort1";
            this.rtbPort1.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedVertical;
            this.rtbPort1.Size = new System.Drawing.Size(547, 404);
            this.rtbPort1.TabIndex = 17;
            this.rtbPort1.Text = "";
            // 
            // rtbPort2
            // 
            this.rtbPort2.Location = new System.Drawing.Point(565, 89);
            this.rtbPort2.Name = "rtbPort2";
            this.rtbPort2.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedVertical;
            this.rtbPort2.Size = new System.Drawing.Size(547, 404);
            this.rtbPort2.TabIndex = 18;
            this.rtbPort2.Text = "";
            // 
            // txtBaud
            // 
            this.txtBaud.Location = new System.Drawing.Point(874, 23);
            this.txtBaud.Name = "txtBaud";
            this.txtBaud.Size = new System.Drawing.Size(75, 20);
            this.txtBaud.TabIndex = 2;
            this.txtBaud.Text = "38400";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "PORT1:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(562, 5);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(46, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "PORT2:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(871, 4);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "BAUD:";
            // 
            // sp1
            // 
            this.sp1.BaudRate = 38400;
            // 
            // sp2
            // 
            this.sp2.BaudRate = 38400;
            this.sp2.PortName = "COM2";
            // 
            // btnDTR
            // 
            this.btnDTR.Location = new System.Drawing.Point(955, 24);
            this.btnDTR.Name = "btnDTR";
            this.btnDTR.Size = new System.Drawing.Size(78, 21);
            this.btnDTR.TabIndex = 4;
            this.btnDTR.Text = "DTR";
            this.btnDTR.UseVisualStyleBackColor = true;
            this.btnDTR.Click += new System.EventHandler(this.btnDTR_Click);
            // 
            // cmbPort1
            // 
            this.cmbPort1.FormattingEnabled = true;
            this.cmbPort1.Location = new System.Drawing.Point(15, 23);
            this.cmbPort1.Name = "cmbPort1";
            this.cmbPort1.Size = new System.Drawing.Size(71, 21);
            this.cmbPort1.TabIndex = 0;
            this.cmbPort1.Text = "COM1";
            // 
            // cmbPort2
            // 
            this.cmbPort2.FormattingEnabled = true;
            this.cmbPort2.Location = new System.Drawing.Point(565, 23);
            this.cmbPort2.Name = "cmbPort2";
            this.cmbPort2.Size = new System.Drawing.Size(82, 21);
            this.cmbPort2.TabIndex = 1;
            this.cmbPort2.Text = "COM1";
            // 
            // btnScanPorts
            // 
            this.btnScanPorts.Location = new System.Drawing.Point(1037, 2);
            this.btnScanPorts.Name = "btnScanPorts";
            this.btnScanPorts.Size = new System.Drawing.Size(75, 20);
            this.btnScanPorts.TabIndex = 6;
            this.btnScanPorts.Text = "Scan Ports";
            this.btnScanPorts.UseVisualStyleBackColor = true;
            this.btnScanPorts.Click += new System.EventHandler(this.btnScanPorts_Click);
            // 
            // txtPort1Data1
            // 
            this.txtPort1Data1.Location = new System.Drawing.Point(15, 63);
            this.txtPort1Data1.Name = "txtPort1Data1";
            this.txtPort1Data1.Size = new System.Drawing.Size(94, 20);
            this.txtPort1Data1.TabIndex = 7;
            this.txtPort1Data1.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort1Data1_PreviewKeyDown);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(48, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Data1-1:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(112, 47);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(48, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "Data1-2:";
            // 
            // txtPort1Data2
            // 
            this.txtPort1Data2.Location = new System.Drawing.Point(115, 63);
            this.txtPort1Data2.Name = "txtPort1Data2";
            this.txtPort1Data2.Size = new System.Drawing.Size(94, 20);
            this.txtPort1Data2.TabIndex = 8;
            this.txtPort1Data2.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort1Data1_PreviewKeyDown);
            // 
            // txtPort1Data3
            // 
            this.txtPort1Data3.Location = new System.Drawing.Point(215, 63);
            this.txtPort1Data3.Name = "txtPort1Data3";
            this.txtPort1Data3.Size = new System.Drawing.Size(94, 20);
            this.txtPort1Data3.TabIndex = 9;
            this.txtPort1Data3.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort1Data1_PreviewKeyDown);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(212, 47);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(48, 13);
            this.label6.TabIndex = 6;
            this.label6.Text = "Data1-3:";
            // 
            // txtPort2Data1
            // 
            this.txtPort2Data1.Location = new System.Drawing.Point(565, 63);
            this.txtPort2Data1.Name = "txtPort2Data1";
            this.txtPort2Data1.Size = new System.Drawing.Size(94, 20);
            this.txtPort2Data1.TabIndex = 12;
            this.txtPort2Data1.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort2Data1_PreviewKeyDown);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(562, 47);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(48, 13);
            this.label7.TabIndex = 6;
            this.label7.Text = "Data2-1:";
            // 
            // txtPort2Data2
            // 
            this.txtPort2Data2.Location = new System.Drawing.Point(665, 63);
            this.txtPort2Data2.Name = "txtPort2Data2";
            this.txtPort2Data2.Size = new System.Drawing.Size(94, 20);
            this.txtPort2Data2.TabIndex = 13;
            this.txtPort2Data2.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort2Data1_PreviewKeyDown);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(662, 47);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(48, 13);
            this.label8.TabIndex = 6;
            this.label8.Text = "Data2-2:";
            // 
            // txtPort2Data3
            // 
            this.txtPort2Data3.Location = new System.Drawing.Point(765, 63);
            this.txtPort2Data3.Name = "txtPort2Data3";
            this.txtPort2Data3.Size = new System.Drawing.Size(94, 20);
            this.txtPort2Data3.TabIndex = 14;
            this.txtPort2Data3.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort2Data1_PreviewKeyDown);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(762, 47);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(48, 13);
            this.label9.TabIndex = 6;
            this.label9.Text = "Data2-3:";
            // 
            // btnClearTerminal
            // 
            this.btnClearTerminal.Location = new System.Drawing.Point(955, 2);
            this.btnClearTerminal.Name = "btnClearTerminal";
            this.btnClearTerminal.Size = new System.Drawing.Size(78, 21);
            this.btnClearTerminal.TabIndex = 5;
            this.btnClearTerminal.Text = "Clear Term";
            this.btnClearTerminal.UseVisualStyleBackColor = true;
            this.btnClearTerminal.Click += new System.EventHandler(this.btnClearTerminal_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // txtPort1Data4
            // 
            this.txtPort1Data4.Location = new System.Drawing.Point(315, 63);
            this.txtPort1Data4.Name = "txtPort1Data4";
            this.txtPort1Data4.Size = new System.Drawing.Size(94, 20);
            this.txtPort1Data4.TabIndex = 10;
            this.txtPort1Data4.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort1Data1_PreviewKeyDown);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(312, 47);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(48, 13);
            this.label10.TabIndex = 6;
            this.label10.Text = "Data1-4:";
            // 
            // txtPort1Data5
            // 
            this.txtPort1Data5.Location = new System.Drawing.Point(415, 63);
            this.txtPort1Data5.Name = "txtPort1Data5";
            this.txtPort1Data5.Size = new System.Drawing.Size(94, 20);
            this.txtPort1Data5.TabIndex = 11;
            this.txtPort1Data5.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort1Data1_PreviewKeyDown);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(412, 47);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(48, 13);
            this.label11.TabIndex = 6;
            this.label11.Text = "Data1-5:";
            // 
            // txtPort2Data4
            // 
            this.txtPort2Data4.Location = new System.Drawing.Point(865, 63);
            this.txtPort2Data4.Name = "txtPort2Data4";
            this.txtPort2Data4.Size = new System.Drawing.Size(94, 20);
            this.txtPort2Data4.TabIndex = 15;
            this.txtPort2Data4.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort2Data1_PreviewKeyDown);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(862, 47);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(48, 13);
            this.label12.TabIndex = 6;
            this.label12.Text = "Data2-4:";
            // 
            // txtPort2Data5
            // 
            this.txtPort2Data5.Location = new System.Drawing.Point(965, 63);
            this.txtPort2Data5.Name = "txtPort2Data5";
            this.txtPort2Data5.Size = new System.Drawing.Size(94, 20);
            this.txtPort2Data5.TabIndex = 16;
            this.txtPort2Data5.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.txtPort2Data1_PreviewKeyDown);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(962, 47);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(48, 13);
            this.label13.TabIndex = 6;
            this.label13.Text = "Data2-5:";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1120, 505);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txtPort2Data5);
            this.Controls.Add(this.txtPort2Data4);
            this.Controls.Add(this.txtPort2Data3);
            this.Controls.Add(this.txtPort2Data2);
            this.Controls.Add(this.txtPort2Data1);
            this.Controls.Add(this.txtPort1Data5);
            this.Controls.Add(this.txtPort1Data4);
            this.Controls.Add(this.txtPort1Data3);
            this.Controls.Add(this.txtPort1Data2);
            this.Controls.Add(this.cmbPort2);
            this.Controls.Add(this.cmbPort1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtPort1Data1);
            this.Controls.Add(this.txtBaud);
            this.Controls.Add(this.rtbPort2);
            this.Controls.Add(this.rtbPort1);
            this.Controls.Add(this.btnScanPorts);
            this.Controls.Add(this.btnClearTerminal);
            this.Controls.Add(this.btnDTR);
            this.Controls.Add(this.btnConnect);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "HC05/06 Bluetooth Terminal";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.RichTextBox rtbPort1;
        private System.Windows.Forms.RichTextBox rtbPort2;
        private System.Windows.Forms.TextBox txtBaud;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.IO.Ports.SerialPort sp1;
        private System.IO.Ports.SerialPort sp2;
        private System.Windows.Forms.Button btnDTR;
        private System.Windows.Forms.ComboBox cmbPort1;
        private System.Windows.Forms.ComboBox cmbPort2;
        private System.Windows.Forms.Button btnScanPorts;
        private System.Windows.Forms.TextBox txtPort1Data1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtPort1Data2;
        private System.Windows.Forms.TextBox txtPort1Data3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtPort2Data1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtPort2Data2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtPort2Data3;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnClearTerminal;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox txtPort1Data4;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtPort1Data5;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtPort2Data4;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox txtPort2Data5;
        private System.Windows.Forms.Label label13;
    }
}

