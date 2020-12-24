using Prism.Mvvm;
using Prism.Commands;
using Prism.Events;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Calculator.Infra.Event;
using System.Collections.ObjectModel;

namespace Calculator.ViewModels
{
    public class GridSize
    {
        public int Depth { get; set; } = default;
        public int Count { get; set; } = default;
        public string Star { get; set; } = default;

    }

    public class ViewerNode
    {
        public int Row { get; set; }
        public int Column { get; set; }
        public string Value { get; set; }
    }

    public class Node
    {
        public Node left;
        public Node right;
        public string value;

        public Node()
        {
            left = null;
            right = null;
        }
        
    }

    
    class TreeViewerViewModel : BindableBase
    {
        private IEventAggregator _ea;

        private string _value;
        public string Value
        {
            get { return _value; }
            set { SetProperty(ref _value, value); }
        }
        

        private int _rowCount;
        public int RowCount
        {
            get { return _rowCount; }
            set { SetProperty(ref _rowCount, value); }
        }

        private string _starRow;
        public string StarRow
        {
            get { return _starRow; }
            set { SetProperty(ref _starRow, value); }
        }


        private ObservableCollection<ViewerNode> _viewerNodes;
        public ObservableCollection<ViewerNode> ViewrNodes
        {
            get { return _viewerNodes; }
            set { SetProperty(ref _viewerNodes, value); }
        }


        private ObservableCollection<GridSize> _gridSize;
        public ObservableCollection<GridSize> GridSize
        {
            get { return _gridSize; }
            set { SetProperty(ref _gridSize, value); }
        }


        // #1 후위연산을 트리형태로 변환
        private void SetTreeViewer(string value)
        {
            string[] array = value.Split('#');

            if (array[array.Length - 1].Equals(""))
            {
                var list = array.ToList();
                list.RemoveAt(list.Count - 1);
                array = list.ToArray();
            }

            Stack<object> stack = new Stack<object>();

            Node main = null;
            Node temp = null;

            int MAXoperChain = 0;
            int operChain = 0;
            foreach (string val in array)
            {
                if(val.Equals("+") || val.Equals("-") || val.Equals("/") || val.Equals("*"))
                {
                    if (main== null)
                    {
                        main = new Node() { value = val };
                        main.right = new Node() { value = stack.Pop().ToString() };
                        main.left = new Node() { value = stack.Pop().ToString() };

                    }
                    else
                    {
                        temp = new Node() { value = val };

                        //오른쪽 노드 처리
                        if (stack.Peek().GetType().Equals(typeof(Node)))
                            temp.right = (Node)stack.Pop();
                        else
                            temp.right = new Node() { value = stack.Pop().ToString() };


                        //왼쪽 노드 처리
                        if (stack.Peek().GetType().Equals(typeof(Node)))
                            temp.left = (Node)stack.Pop();
                        else
                            temp.left = new Node() { value = stack.Pop().ToString() };

                        main = temp;
                    }

                    stack.Push(main);

                    operChain++;
                    if (MAXoperChain < operChain)
                        MAXoperChain = operChain;
                }
                else
                {
                    stack.Push(val);
                    
                    operChain = 0;
                }
            }

            
            _viewerNodes = new ObservableCollection<ViewerNode>();

            int depth = 0;
            if(main != null)
                Search(main , ref depth);

            SetGridSize(depth + 1);

            foreach (ViewerNode n in _viewerNodes)
            {
                Value = $"{ n.Value } :: ({n.Row}, {n.Column}) ,";
            }

        }
        
        //#2 트리형태를 나열형태로 변환(추가)
        private void Search(Node node, ref int maxDepth, int depth = 0, int pivot = 0)
        {
            _viewerNodes.Add(new ViewerNode() { Value = node.value, Row = depth, Column = pivot });
            if (node.left != null)
                Search( node.left, ref maxDepth, depth + 1, pivot * 2);

            if (node.right != null)
                Search(node.right, ref maxDepth, depth + 1, (pivot * 2) + 1);

            if (depth > maxDepth)
                maxDepth = depth;
            return;
        }


        //#2.5 트리의 깊이를 기준으로 그리드 크기를 설정
        private void SetGridSize(int depth)
        {
            RowCount = depth;

            List<int> list = new List<int>();
            for (int j = 0; j < depth; j++)
                list.Add(j);
            StarRow = list.Aggregate("", (a, b) => a + "," + b);
            

            _gridSize = new ObservableCollection<GridSize>();
            for (int i = 0; i < depth; i++)
            {
                int size = (int)Math.Pow(2, i);

                list = new List<int>();
                for (int j = 0; j < size; j++)
                    list.Add(j);

                GridSize.Add(new GridSize()
                {
                    Depth = i,
                    Count = size,
                    Star = list.Aggregate("", (a, b) => a + "," + b)
                });
            }
        }
        
        public TreeViewerViewModel(IEventAggregator ea)
        {
            SetGridSize(1);

            _ea = ea;
            _ea.GetEvent<SendTreeViewerDataEvent>().Subscribe(SetTreeViewer);

            GridSize = new ObservableCollection<GridSize>();
            //SetTreeViewer("9#3#+#3#+#"); //"9#3#+#3#+#"//629#258#*#3#+#



            //RowCount = 5;
            //ColumnCount = 5;
            //StarColumn = "0,1,2,3,4";
            //StarRow = "0,1,2,3,4";
        }

    }
}
