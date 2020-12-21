using Calculator.Infra.Model;
using Prism.Events;
using System.Collections.Generic;

namespace Calculator.Infra.Service
{
    public class Repository : IRepository
    {
        public IEventAggregator _ea{ get; set; }
        public List<Log> LogList { get; }

        public Repository(IEventAggregator ea)
        {
            _ea = ea;
        }
    }
}
