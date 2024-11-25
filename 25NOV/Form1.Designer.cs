namespace TestUDP
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.AbortBouton = new System.Windows.Forms.Button();
            this.SuiveurBouton = new System.Windows.Forms.Button();
            this.ManuelBouton = new System.Windows.Forms.Button();
            this.MessageIN = new System.Windows.Forms.TextBox();
            this.MessageOUT = new System.Windows.Forms.TextBox();
            this.Gauche = new System.Windows.Forms.Button();
            this.Recule = new System.Windows.Forms.Button();
            this.Avance = new System.Windows.Forms.Button();
            this.STOP = new System.Windows.Forms.Button();
            this.Droite = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // AbortBouton
            // 
            this.AbortBouton.BackColor = System.Drawing.Color.Red;
            this.AbortBouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AbortBouton.Location = new System.Drawing.Point(40, 35);
            this.AbortBouton.Margin = new System.Windows.Forms.Padding(2);
            this.AbortBouton.Name = "AbortBouton";
            this.AbortBouton.Size = new System.Drawing.Size(87, 41);
            this.AbortBouton.TabIndex = 0;
            this.AbortBouton.Text = "ModeAbort";
            this.AbortBouton.UseVisualStyleBackColor = false;
            this.AbortBouton.Click += new System.EventHandler(this.AbortBouton_Click);
            // 
            // SuiveurBouton
            // 
            this.SuiveurBouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SuiveurBouton.Location = new System.Drawing.Point(40, 81);
            this.SuiveurBouton.Margin = new System.Windows.Forms.Padding(2);
            this.SuiveurBouton.Name = "SuiveurBouton";
            this.SuiveurBouton.Size = new System.Drawing.Size(87, 36);
            this.SuiveurBouton.TabIndex = 1;
            this.SuiveurBouton.Text = "ModeSuiveur";
            this.SuiveurBouton.UseVisualStyleBackColor = true;
            this.SuiveurBouton.Click += new System.EventHandler(this.SuiveurBouton_Click);
            // 
            // ManuelBouton
            // 
            this.ManuelBouton.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ManuelBouton.Location = new System.Drawing.Point(40, 122);
            this.ManuelBouton.Margin = new System.Windows.Forms.Padding(2);
            this.ManuelBouton.Name = "ManuelBouton";
            this.ManuelBouton.Size = new System.Drawing.Size(87, 37);
            this.ManuelBouton.TabIndex = 2;
            this.ManuelBouton.Text = "ModeManuel";
            this.ManuelBouton.UseVisualStyleBackColor = true;
            this.ManuelBouton.Click += new System.EventHandler(this.ManuelBouton_Click);
            // 
            // MessageIN
            // 
            this.MessageIN.Location = new System.Drawing.Point(320, 90);
            this.MessageIN.Margin = new System.Windows.Forms.Padding(2);
            this.MessageIN.Name = "MessageIN";
            this.MessageIN.Size = new System.Drawing.Size(269, 20);
            this.MessageIN.TabIndex = 3;
            // 
            // MessageOUT
            // 
            this.MessageOUT.Location = new System.Drawing.Point(178, 90);
            this.MessageOUT.Margin = new System.Windows.Forms.Padding(2);
            this.MessageOUT.Name = "MessageOUT";
            this.MessageOUT.Size = new System.Drawing.Size(112, 20);
            this.MessageOUT.TabIndex = 4;
            // 
            // Gauche
            // 
            this.Gauche.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Gauche.Location = new System.Drawing.Point(60, 206);
            this.Gauche.Margin = new System.Windows.Forms.Padding(2);
            this.Gauche.Name = "Gauche";
            this.Gauche.Size = new System.Drawing.Size(87, 37);
            this.Gauche.TabIndex = 5;
            this.Gauche.Text = "Gauche";
            this.Gauche.UseVisualStyleBackColor = true;
            this.Gauche.Click += new System.EventHandler(this.Gauche_Click);
            // 
            // Recule
            // 
            this.Recule.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Recule.Location = new System.Drawing.Point(158, 227);
            this.Recule.Margin = new System.Windows.Forms.Padding(2);
            this.Recule.Name = "Recule";
            this.Recule.Size = new System.Drawing.Size(87, 37);
            this.Recule.TabIndex = 7;
            this.Recule.Text = "Recule";
            this.Recule.UseVisualStyleBackColor = true;
            this.Recule.Click += new System.EventHandler(this.Recule_Click);
            // 
            // Avance
            // 
            this.Avance.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Avance.Location = new System.Drawing.Point(158, 177);
            this.Avance.Margin = new System.Windows.Forms.Padding(2);
            this.Avance.Name = "Avance";
            this.Avance.Size = new System.Drawing.Size(87, 37);
            this.Avance.TabIndex = 8;
            this.Avance.Text = "Avance";
            this.Avance.UseVisualStyleBackColor = true;
            this.Avance.Click += new System.EventHandler(this.Avance_Click);
            // 
            // STOP
            // 
            this.STOP.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.STOP.Location = new System.Drawing.Point(158, 297);
            this.STOP.Margin = new System.Windows.Forms.Padding(2);
            this.STOP.Name = "STOP";
            this.STOP.Size = new System.Drawing.Size(87, 37);
            this.STOP.TabIndex = 9;
            this.STOP.Text = "STOP";
            this.STOP.UseVisualStyleBackColor = true;
            this.STOP.Click += new System.EventHandler(this.STOP_Click);
            // 
            // Droite
            // 
            this.Droite.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Droite.Location = new System.Drawing.Point(260, 206);
            this.Droite.Margin = new System.Windows.Forms.Padding(2);
            this.Droite.Name = "Droite";
            this.Droite.Size = new System.Drawing.Size(87, 37);
            this.Droite.TabIndex = 10;
            this.Droite.Text = "Droite";
            this.Droite.UseVisualStyleBackColor = true;
            this.Droite.Click += new System.EventHandler(this.Droite_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(600, 366);
            this.Controls.Add(this.Droite);
            this.Controls.Add(this.STOP);
            this.Controls.Add(this.Avance);
            this.Controls.Add(this.Recule);
            this.Controls.Add(this.Gauche);
            this.Controls.Add(this.MessageOUT);
            this.Controls.Add(this.MessageIN);
            this.Controls.Add(this.ManuelBouton);
            this.Controls.Add(this.SuiveurBouton);
            this.Controls.Add(this.AbortBouton);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button AbortBouton;
        private System.Windows.Forms.Button SuiveurBouton;
        private System.Windows.Forms.Button ManuelBouton;
        private System.Windows.Forms.TextBox MessageIN;
        private System.Windows.Forms.TextBox MessageOUT;
        private System.Windows.Forms.Button Gauche;
        private System.Windows.Forms.Button Recule;
        private System.Windows.Forms.Button Avance;
        private System.Windows.Forms.Button STOP;
        private System.Windows.Forms.Button Droite;
    }
}

