using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
[RequireComponent(typeof(MeshFilter))]
[RequireComponent(typeof(MeshRenderer))]
public class SpriteRenderer : MonoBehaviour
{
	#region Components 
	struct Components
	{
		public MeshFilter	meshFilter;
		public MeshRenderer	meshRenderer;
	}
	
	private Components components;
	#endregion 

	void Awake ()
	{
		this.components = new Components()
		{
			meshFilter = GetComponent<MeshFilter>(),
			meshRenderer = GetComponent<MeshRenderer>()
		};

		this.components.meshFilter.sharedMesh = CreateMesh();
		this.components.meshRenderer.castShadows = false;
		this.components.meshRenderer.receiveShadows = false;
	}

	void Update ()
	{
		if (this.components.meshRenderer == null)
		{
			return;
		}

		Material sharedMaterial = this.components.meshRenderer.sharedMaterial;
		
		if (sharedMaterial == null)
		{
			return;
		}

		if (sharedMaterial.mainTexture == null)
		{
			return;
		}

		float widthRequired = sharedMaterial.mainTexture.width * sharedMaterial.mainTextureScale.x;
		float heightRequired = sharedMaterial.mainTexture.height;

		float ratioRequired = widthRequired / heightRequired;
		float ratioRendered = transform.localScale.x / transform.localScale.y;

		if (ratioRequired != ratioRendered)
		{
			transform.localScale = new Vector3
			(
				transform.localScale.x,
				transform.localScale.x / ratioRequired,
				transform.localScale.z
			);
		}
	}

	private Mesh CreateMesh ()
	{
		Vector2[] uv = new Vector2[]
		{
			new Vector2(0.0f, 1.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f)
		};
		
		Vector3[] vertices = new Vector3[]
		{
			new Vector3(-0.5f, 0.5f, 0.0f),
			new Vector3(0.5f, 0.5f, 0.0f),
			new Vector3(-0.5f, -0.5f, 0.0f),
			new Vector3(0.5f, -0.5f, 0.0f)
		};
		
		int[] triangles = new int[]
		{
			0, 1, 2,
			2, 1, 3 
		};
		
		Mesh mesh = new Mesh();

		mesh.name = "Sprite Mesh";
		mesh.hideFlags = HideFlags.DontSave;
		mesh.vertices = vertices;
		mesh.uv = uv;
		mesh.triangles = triangles;
		mesh.RecalculateBounds();
		mesh.RecalculateNormals();

		return mesh;
	}
}