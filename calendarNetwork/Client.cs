using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;

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
            
            _Tcplient = new TcpClient(_Endpoint.Ip,_Endpoint.Port);
            if (_Endpoint == null)
                return false;


            _IsConnnect = true;
            return true;
        }





    }
}
