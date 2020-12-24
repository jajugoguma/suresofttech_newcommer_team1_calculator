using Prism.Events;

using System.Collections.Generic;

using CalendarNetworkClient;
using Calculator.Infra.Model;

namespace Calculator.Infra.Service
{
    public interface IRepository
    {
        List<Log> LogList { get; set; }
        void ResetLog();
        void AddLog(Log log);
        Client Client { get; set; }
        string IP { get; set; }
        string Port { get; set; }
        int TailCnt { get; set; }

        bool ServerCalculateFlagCheck { get; set; }

    }
}