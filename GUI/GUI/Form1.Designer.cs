namespace GUI
{
    partial class chiSquared
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
            this.importCSVButton = new System.Windows.Forms.Button();
            this.calculateButton = new System.Windows.Forms.Button();
            this.titleText = new System.Windows.Forms.Label();
            this.yourCSVText = new System.Windows.Forms.Label();
            this.enterPText = new System.Windows.Forms.Label();
            this.displayCSVText = new System.Windows.Forms.TextBox();
            this.pvalText = new System.Windows.Forms.TextBox();
            this.helpButton = new System.Windows.Forms.Button();
            this.exitButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // importCSVButton
            // 
            this.importCSVButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.importCSVButton.Location = new System.Drawing.Point(459, 153);
            this.importCSVButton.Name = "importCSVButton";
            this.importCSVButton.Size = new System.Drawing.Size(131, 22);
            this.importCSVButton.TabIndex = 0;
            this.importCSVButton.Text = "Import CSV File";
            this.importCSVButton.UseVisualStyleBackColor = true;
            this.importCSVButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // calculateButton
            // 
            this.calculateButton.Location = new System.Drawing.Point(459, 385);
            this.calculateButton.Name = "calculateButton";
            this.calculateButton.Size = new System.Drawing.Size(138, 33);
            this.calculateButton.TabIndex = 1;
            this.calculateButton.Text = "Calculate";
            this.calculateButton.UseVisualStyleBackColor = true;
            // 
            // titleText
            // 
            this.titleText.AutoSize = true;
            this.titleText.Font = new System.Drawing.Font("Garamond", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.titleText.ForeColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.titleText.Location = new System.Drawing.Point(206, 9);
            this.titleText.Name = "titleText";
            this.titleText.Size = new System.Drawing.Size(274, 39);
            this.titleText.TabIndex = 2;
            this.titleText.Text = "Chi Squared Test";
            this.titleText.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // yourCSVText
            // 
            this.yourCSVText.AutoSize = true;
            this.yourCSVText.Font = new System.Drawing.Font("Garamond", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.yourCSVText.Location = new System.Drawing.Point(71, 146);
            this.yourCSVText.Name = "yourCSVText";
            this.yourCSVText.Size = new System.Drawing.Size(223, 27);
            this.yourCSVText.TabIndex = 3;
            this.yourCSVText.Text = "Your CSV FIle Name:";
            // 
            // enterPText
            // 
            this.enterPText.AutoSize = true;
            this.enterPText.Font = new System.Drawing.Font("Garamond", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.enterPText.Location = new System.Drawing.Point(131, 230);
            this.enterPText.Name = "enterPText";
            this.enterPText.Size = new System.Drawing.Size(163, 27);
            this.enterPText.TabIndex = 4;
            this.enterPText.Text = "Enter a P-value:";
            // 
            // displayCSVText
            // 
            this.displayCSVText.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.displayCSVText.Enabled = false;
            this.displayCSVText.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.displayCSVText.Location = new System.Drawing.Point(300, 153);
            this.displayCSVText.Name = "displayCSVText";
            this.displayCSVText.Size = new System.Drawing.Size(129, 22);
            this.displayCSVText.TabIndex = 5;
            // 
            // pvalText
            // 
            this.pvalText.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.pvalText.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pvalText.ForeColor = System.Drawing.SystemColors.WindowText;
            this.pvalText.Location = new System.Drawing.Point(304, 237);
            this.pvalText.Name = "pvalText";
            this.pvalText.Size = new System.Drawing.Size(125, 22);
            this.pvalText.TabIndex = 6;
            // 
            // helpButton
            // 
            this.helpButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.helpButton.Font = new System.Drawing.Font("Garamond", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.helpButton.Location = new System.Drawing.Point(614, 23);
            this.helpButton.Name = "helpButton";
            this.helpButton.Size = new System.Drawing.Size(58, 25);
            this.helpButton.TabIndex = 7;
            this.helpButton.Text = "Help";
            this.helpButton.UseVisualStyleBackColor = true;
            this.helpButton.Click += new System.EventHandler(this.helpButton_Click);
            // 
            // exitButton
            // 
            this.exitButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.exitButton.Location = new System.Drawing.Point(12, 385);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(138, 33);
            this.exitButton.TabIndex = 8;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
            // 
            // chiSquared
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(684, 461);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.helpButton);
            this.Controls.Add(this.pvalText);
            this.Controls.Add(this.displayCSVText);
            this.Controls.Add(this.enterPText);
            this.Controls.Add(this.yourCSVText);
            this.Controls.Add(this.titleText);
            this.Controls.Add(this.calculateButton);
            this.Controls.Add(this.importCSVButton);
            this.HelpButton = true;
            this.Name = "chiSquared";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Chi Squared";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button importCSVButton;
        private System.Windows.Forms.Button calculateButton;
        private System.Windows.Forms.Label titleText;
        private System.Windows.Forms.Label yourCSVText;
        private System.Windows.Forms.Label enterPText;
        private System.Windows.Forms.TextBox displayCSVText;
        private System.Windows.Forms.TextBox pvalText;
        private System.Windows.Forms.Button helpButton;
        private System.Windows.Forms.Button exitButton;
    }
}

