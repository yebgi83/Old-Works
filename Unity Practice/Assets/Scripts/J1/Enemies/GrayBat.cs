using UnityEngine;
using System.Collections;

[RequireComponent(typeof(SpriteAnimationRenderer))]
public class GrayBat : MonoBehaviour 
{
	#region Components 
	struct Components
	{
		public SpriteAnimationRenderer spriteAnimationRenderer;
	}
	
	private Components components;
	#endregion
	
	#region Variables
	public SpriteAnimation defaultAnimation;
	#endregion
	
	void Awake () 
	{
		this.components = new Components()
		{
			spriteAnimationRenderer = GetComponent<SpriteAnimationRenderer>()
		};
		
		this.components.spriteAnimationRenderer.Play (defaultAnimation, true);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
