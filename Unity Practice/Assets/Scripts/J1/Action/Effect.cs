
using UnityEngine;
using System.Collections;

namespace JJBJ.J1.Action
{
	public class Effect
	{
		public event System.Action OnBegin;
		public event System.Action OnContinue;
		public event System.Action OnEnd;

		private float? beginTick;
		private float? retainTick;

		public bool isContinued 
		{
			get;
			private set;
		}

		public void Begin (MonoBehaviour target, float retainTick)
		{
			if (this.isContinued == false)
			{
				this.isContinued = true;
				target.StartCoroutine (Continue(target, retainTick));
			}
			else
			{
				this.retainTick += retainTick;
				RaiseEvent (OnContinue);
			}
		}
		
		private IEnumerator Continue (MonoBehaviour target, float retainTick)
		{
			RaiseEvent (OnBegin);
			
			this.beginTick = Time.time;
			this.retainTick = retainTick;
			
			while (this.isContinued == true)
			{
				float deltaRetainTick = Time.time - this.beginTick.Value;
				
				if (deltaRetainTick > this.retainTick)
				{
					End (target);
				}
				
				yield return null;
			}
		}
		
		public void End (MonoBehaviour target)
		{
			this.beginTick = null;
			this.retainTick = null;
			this.isContinued = false;
			
			RaiseEvent (OnEnd);
		}
		
		private void RaiseEvent (System.Action raiseEvent)
		{
			if (raiseEvent != null) 
			{
				raiseEvent ();
			}
		}
	}
}