using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TestUDP
{

    public partial class Form1 : Form
    {


        
        string ipAddress = "192.168.1.127"; //A CHANGER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        private const int port = 8080;
        NetworkStream stream;
        string messageToSend;
        UdpClient udpClient ;
        
        private CancellationTokenSource cts = new CancellationTokenSource();
        public Form1()
        {
            InitializeComponent();
        }

        private async void Form1_Load(object sender, EventArgs e)
        {
            await Task.Run(() => udpReceive(cts.Token));
        }
        private async Task udpReceive(CancellationToken cancellationToken)
        {
            udpClient = new UdpClient(port);
            IPEndPoint remoteEndPoint = new IPEndPoint(IPAddress.Any, port);
            try
            {
                while (!cts.Token.IsCancellationRequested)
                {
                    UdpReceiveResult receiveResult = await udpClient.ReceiveAsync();
                    string receiveData = Encoding.ASCII.GetString(receiveResult.Buffer);

                    this.Invoke(new MethodInvoker(delegate ()
                    {
                        if(receiveData == "Abort")
                        {
                            MessageIN.Text = "Abort";
                        }
                        else if (receiveData == "Manuel")
                        {
                            MessageIN.Text = "Manuel";
                        }
                        if (receiveData == "Suiveur")
                        {
                            MessageIN.Text = "Suiveur";
                        }

                    }));

                }
            }
            catch(SocketException ex)
            {
                MessageBox.Show($"Erreur réseau : {ex.Message}");

            }
            finally
            {
                udpClient.Close();
            }
        }
        private async Task udpSend(string sendData)
        {
            try
            {
                byte[] sendbytes = Encoding.ASCII.GetBytes(sendData);
                await udpClient.SendAsync(sendbytes, sendbytes.Length, ipAddress, port);
            }
            catch (ObjectDisposedException)
            {
                MessageBox.Show("Erreur : Tentative d'envoi après la fermeture du client UDP");
            }
            catch(SocketException ex)
            {
                MessageBox.Show($"Erreur d'envoi UDP : {ex.Message}");
            }

        }
        private void SetButtonText(string text)
        {
            if (AbortBouton.InvokeRequired)
            {
                AbortBouton.Invoke(new Action(() => MessageOUT.Text = text));
            }
            else
            {
                MessageOUT.Text = text;
            }
        }
        private async void AbortBouton_Click(object sender, EventArgs e)
        {
            //string sendData = (MessageOUT.Text == "ON" ? "OFF" : "ON");
            //SetButtonText(sendData);
            //await udpSend(sendData);

            messageToSend = "Abort";
            await udpSend(messageToSend);
        }

        private async void SuiveurBouton_Click(object sender, EventArgs e)
        {
            messageToSend = "Suiveur";
            await udpSend(messageToSend);
        }

        private async void ManuelBouton_Click(object sender, EventArgs e)
        {
            messageToSend = "Manuel";
            await udpSend(messageToSend);
        }

        private async void Avance_Click(object sender, EventArgs e)
        {
            messageToSend = "Avance";
            await udpSend(messageToSend);
        }

        private async void Recule_Click(object sender, EventArgs e)
        {
            messageToSend = "Recule";
            await udpSend(messageToSend);
        }

        private async void Gauche_Click(object sender, EventArgs e)
        {
            messageToSend = "Gauche";
            await udpSend(messageToSend);
        }

        private async void Droite_Click(object sender, EventArgs e)
        {
            messageToSend = "Droite";
            await udpSend(messageToSend);
        }

        private async void STOP_Click(object sender, EventArgs e)
        {
            messageToSend = "Stop";
            await udpSend(messageToSend);
        }

    }
}
