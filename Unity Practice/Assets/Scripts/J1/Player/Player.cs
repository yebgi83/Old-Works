using UnityEngine;
using System.Collections;

using JJBJ.J1.Action;
using JJBJ.TouchListener;

[RequireComponent(typeof(CharacterController))]
[RequireComponent(typeof(SpriteAnimationRenderer))]
public class Player : MonoBehaviour 
{
	#region Components 
	struct Components
	{
		public CharacterController characterController;
		public SpriteAnimationRenderer spriteAnimationRenderer;
	}
	
	private Components components;
	#endregion
	
	#region Variables
	public SpriteAnimation defaultAnimation;

	private TouchListener touchListener;
	private Jump jumpAction;
	#endregion

	void Awake () 
	{
		this.components.characterController = GetComponent<CharacterController> ();
		this.components.spriteAnimationRenderer = GetComponent<SpriteAnimationRenderer> ();
		this.components.spriteAnimationRenderer.Play (defaultAnimation, true);

		this.touchListener = new TouchListener ();
		this.touchListener.OnBegin += OnTouchBegin;
		this.touchListener.Begin (this);

		this.jumpAction = new Jump ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnTouchBegin (Vector2 position)
	{
		this.jumpAction.Begin
		(
			this,
			this.components.characterController,
			new Vector2(0.0f, 0.1f),
			new Vector2(0.0f, -0.01f)
		);
	}
}
