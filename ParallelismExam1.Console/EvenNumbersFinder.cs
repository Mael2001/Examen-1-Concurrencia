using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ParallelismExam1.Console
{
    public class EvenNumbersFinder
    {
        private readonly IEnumerable<int> _values;

        public EvenNumbersFinder(IEnumerable<int> values)
        {
            this._values = values;
        }

        public IEnumerable<int> Execute()
        {
            return FindEvenNumbers(_values.ToArray(), 0, _values.Count());
        }

        private IEnumerable<int> FindEvenNumbers(int[] listOfValues, int start, int end)
        {

            var evenNumbers = new ConcurrentBag<int>();
            Parallel.ForEach(listOfValues, (tmp) =>
            {
                if (tmp %2 ==0)
                {
                    evenNumbers.Add(tmp);
                }
            });
            return evenNumbers;
        }
    }
}
