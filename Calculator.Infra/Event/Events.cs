using Prism.Events;
using Calculator.Infra.Model;

namespace Calculator.Infra.Event
{
    public class SampleEvent : PubSubEvent<string> { }
    public class UpdateLogEvent : PubSubEvent { }
    

}
