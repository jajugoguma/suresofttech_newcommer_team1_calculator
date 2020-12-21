using Prism.Events;
using Calculator.Infra.Model;
using System;

namespace Calculator.Infra.Event
{
    public class SampleEvent : PubSubEvent<string> { }
    public class UpdateLogEvent : PubSubEvent { }

    public class EditCalculatorValueEvent : PubSubEvent<string> { }
    public class SendPopupOption : PubSubEvent<Tuple<string, string, string>> { }


}
