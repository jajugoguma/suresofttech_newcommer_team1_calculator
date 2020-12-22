using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Threading;

namespace CalendarNetworkClient
{
    public class EndPoint
    {
        public string Ip;
        public int Port;
        public EndPoint(string ip ,string stringPort)
        {
            int port = Convert.ToInt32(stringPort);
            SetUp(ip, port);
        }
        void SetUp(string ip , int port)
        {
            Ip = ip;
            Port = port;
        }
    }
    public class Client
    {
        TcpClient _Tcplient;
        EndPoint _Endpoint;
        NetworkStream stream;
        bool _IsConnnect;

        public Client()
        {
            _IsConnnect = false;
            _Endpoint = null;
        }
        public Client(EndPoint endPoint) : this()
        {
            SetEndPoint(endPoint);
        }
        public void SetEndPoint(EndPoint endPoint)
        {
            _Endpoint = endPoint;
        }
        public bool Connect()
        {
            if (_Endpoint == null)
                return false;

            try
            {
                _Tcplient = new TcpClient(_Endpoint.Ip, _Endpoint.Port);
                stream = _Tcplient.GetStream();
                stream.ReadTimeout = 10;
                stream.WriteTimeout = 10;
            }
            catch (Exception)
            {
                return false;
            }

            KeepalivedCheck();
            _IsConnnect = true;
            return true;
        }


        public void KeepalivedCheck()
        {
            Thread t = new Thread(new ThreadStart(() =>
            {
                while (_IsConnnect) {
                    Thread.Sleep(100);
                    try
                    {
                        Send("");
                    }
                    catch
                    {
                        if (ReConnect() != true)
                        {
                            continue;
                        }
                        _IsConnnect = false;
                    }
                }
            }));
            t.IsBackground = true;
            t.Start();

        }
        void DisConnect()
        {
        }
        public void Send(string message)
        {
            byte[] buff = Encoding.Unicode.GetBytes(message);
            stream.Write(buff, 0, buff.Length);

        }
        public string Recv()
        {
            byte[] outbuf = new byte[1024];
            int nbytes = 0;
            try
            {
                nbytes = stream.Read(outbuf, 0, outbuf.Length);
            }
            catch (Exception)
            {

            }
            string output = Encoding.Unicode.GetString(outbuf, 0, nbytes);
            return output;
        }
    
private bool ReConnect()
        {
            bool isConnect = false;
            for (int i = 0; i < 5; ++i)
            {
                isConnect = Connect();
                if (isConnect == true)
                {
                    return true;
                }
                Thread.Sleep(1000);
            }
            return isConnect;
        }

    }
}
