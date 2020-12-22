using Prism.Events;

using System.Collections.Generic;
using CalendarNetworkClient;

using Calculator.Infra.Model;
using Calculator.Infra.Event;

namespace Calculator.Infra.Service
{
    public class Repository : IRepository
    {
        public IEventAggregator _ea { get; private set; }
        public List<Log> LogList { get; set; }

        public Client Client { get; set; }
        public string IP { get; set; }
        public string Port { get; set; }

        public void ResetLog()
        {
            LogList.Clear();
        }

        public void AddLog(Log log)
        {
            LogList.Add(log);
            _ea.GetEvent<UpdateLogEvent>().Publish();

        }

        public Repository(IEventAggregator ea)
        {
            _ea = ea;

            LogList = new List<Log>();
            Client = new Client();

            IP = "127.0.0.1";
            Port = "18000";
        }
    }
}
