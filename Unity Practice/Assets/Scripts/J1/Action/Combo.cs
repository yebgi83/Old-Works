using UnityEngine;
using System.Collections;

namespace JJBJ.J1.Action
{
	public class Combo
	{
		public event System.Action OnBegin;
		public event System.Action OnContinue;
		public event System.Action OnEnd;
		
		private float? beginTick;
		private float? retainTick;
		
		private bool isContiuned;
		
		public int comboCount
		{
			get;
			private set;
		}
		
		public void Begin (MonoBehaviour target, float retainTick)
		{
			if (this.isContiuned == false)
			{
				this.isContiuned = true;
				target.StartCoroutine (Continue(target, retainTick));
			}
			else
			{
				this.beginTick = Time.time;
				this.retainTick = retainTick;
				this.comboCount++;
				
				RaiseEvent (OnContinue);
			}
		}
		
		private IEnumerator Continue (MonoBehaviour target, float retainTick)
		{
			RaiseEvent (OnBegin);
			
			this.beginTick = Time.time;
			this.retainTick = retainTick;
			this.comboCount = 0;

			while (this.isContiuned == true)
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
			this.isContiuned = false;
			this.comboCount = 0;	
			
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
