using Prism.Events;
using System.Collections.Generic;

using Calculator.Infra.Model;
using Calculator.Infra.Event;

namespace Calculator.Infra.Service
{
    public class Repository : IRepository
    {
        public IEventAggregator _ea { get; private set; }
        public List<Log> LogList { get; set; }

        public Repository(IEventAggregator ea)
        {
            _ea = ea;

            LogList = new List<Log>();
        }

        public void ResetLog()
        {
            LogList.Clear();
        }

        public void AddLog(Log log)
        {
            LogList.Add(log);
            _ea.GetEvent<UpdateLogEvent>().Publish();

        }
    }
}
