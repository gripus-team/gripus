/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class aiMesh : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal aiMesh(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(aiMesh obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~aiMesh() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          AssimpPINVOKE.delete_aiMesh(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public aiVector3DVector mBitangents { get { return GetmBitangents(); } }
  public aiBoneVector mBones { get { return GetmBones(); } }
  public aiColor4DVectorVector mColors { get { return GetmColors(); } }
  public aiFaceVector mFaces { get { return GetmFaces(); } }
  public aiVector3DVector mNormals { get { return GetmNormals(); } }
  public aiVector3DVector mTangents { get { return GetmTangents(); } }
  public aiVector3DVectorVector mTextureCoords { get { return GetmTextureCoords(); } }
  public aiVector3DVector mVertices { get { return GetmVertices(); } }

  public aiPrimitiveType mPrimitiveTypes {
    set {
      AssimpPINVOKE.aiMesh_mPrimitiveTypes_set(swigCPtr, (uint)value);
    }  get { return (aiPrimitiveType)AssimpPINVOKE.aiMesh_mPrimitiveTypes_get(swigCPtr); } 
  }

  public uint mNumVertices {
    set {
      AssimpPINVOKE.aiMesh_mNumVertices_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiMesh_mNumVertices_get(swigCPtr);
      return ret;
    } 
  }

  public uint mNumFaces {
    set {
      AssimpPINVOKE.aiMesh_mNumFaces_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiMesh_mNumFaces_get(swigCPtr);
      return ret;
    } 
  }

  public uint mNumBones {
    set {
      AssimpPINVOKE.aiMesh_mNumBones_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiMesh_mNumBones_get(swigCPtr);
      return ret;
    } 
  }

  public uint mMaterialIndex {
    set {
      AssimpPINVOKE.aiMesh_mMaterialIndex_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiMesh_mMaterialIndex_get(swigCPtr);
      return ret;
    } 
  }

  public aiString mName {
    set {
      AssimpPINVOKE.aiMesh_mName_set(swigCPtr, aiString.getCPtr(value));
    } 
    get {
      IntPtr cPtr = AssimpPINVOKE.aiMesh_mName_get(swigCPtr);
      aiString ret = (cPtr == IntPtr.Zero) ? null : new aiString(cPtr, false);
      return ret;
    } 
  }

  public uint mNumAnimMeshes {
    set {
      AssimpPINVOKE.aiMesh_mNumAnimMeshes_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiMesh_mNumAnimMeshes_get(swigCPtr);
      return ret;
    } 
  }

  public aiMesh() : this(AssimpPINVOKE.new_aiMesh(), true) {
  }

  public bool HasPositions() {
    bool ret = AssimpPINVOKE.aiMesh_HasPositions(swigCPtr);
    return ret;
  }

  public bool HasFaces() {
    bool ret = AssimpPINVOKE.aiMesh_HasFaces(swigCPtr);
    return ret;
  }

  public bool HasNormals() {
    bool ret = AssimpPINVOKE.aiMesh_HasNormals(swigCPtr);
    return ret;
  }

  public bool HasTangentsAndBitangents() {
    bool ret = AssimpPINVOKE.aiMesh_HasTangentsAndBitangents(swigCPtr);
    return ret;
  }

  public bool HasVertexColors(uint pIndex) {
    bool ret = AssimpPINVOKE.aiMesh_HasVertexColors(swigCPtr, pIndex);
    return ret;
  }

  public bool HasTextureCoords(uint pIndex) {
    bool ret = AssimpPINVOKE.aiMesh_HasTextureCoords(swigCPtr, pIndex);
    return ret;
  }

  public uint GetNumUVChannels() {
    uint ret = AssimpPINVOKE.aiMesh_GetNumUVChannels(swigCPtr);
    return ret;
  }

  public uint GetNumColorChannels() {
    uint ret = AssimpPINVOKE.aiMesh_GetNumColorChannels(swigCPtr);
    return ret;
  }

  public bool HasBones() {
    bool ret = AssimpPINVOKE.aiMesh_HasBones(swigCPtr);
    return ret;
  }

  private aiAnimMeshVector GetmAnimMeshes() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmAnimMeshes(swigCPtr);
    aiAnimMeshVector ret = (cPtr == IntPtr.Zero) ? null : new aiAnimMeshVector(cPtr, true);
    return ret;
  }

  private aiVector3DVector GetmBitangents() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmBitangents(swigCPtr);
    aiVector3DVector ret = (cPtr == IntPtr.Zero) ? null : new aiVector3DVector(cPtr, true);
    return ret;
  }

  private aiBoneVector GetmBones() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmBones(swigCPtr);
    aiBoneVector ret = (cPtr == IntPtr.Zero) ? null : new aiBoneVector(cPtr, true);
    return ret;
  }

  private aiColor4DVectorVector GetmColors() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmColors(swigCPtr);
    aiColor4DVectorVector ret = (cPtr == IntPtr.Zero) ? null : new aiColor4DVectorVector(cPtr, true);
    return ret;
  }

  private aiFaceVector GetmFaces() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmFaces(swigCPtr);
    aiFaceVector ret = (cPtr == IntPtr.Zero) ? null : new aiFaceVector(cPtr, true);
    return ret;
  }

  private aiVector3DVector GetmNormals() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmNormals(swigCPtr);
    aiVector3DVector ret = (cPtr == IntPtr.Zero) ? null : new aiVector3DVector(cPtr, true);
    return ret;
  }

  private aiVector3DVector GetmTangents() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmTangents(swigCPtr);
    aiVector3DVector ret = (cPtr == IntPtr.Zero) ? null : new aiVector3DVector(cPtr, true);
    return ret;
  }

  private aiVector3DVectorVector GetmTextureCoords() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmTextureCoords(swigCPtr);
    aiVector3DVectorVector ret = (cPtr == IntPtr.Zero) ? null : new aiVector3DVectorVector(cPtr, true);
    return ret;
  }

  private UintVector GetmNumUVComponents() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmNumUVComponents(swigCPtr);
    UintVector ret = (cPtr == IntPtr.Zero) ? null : new UintVector(cPtr, true);
    return ret;
  }

  private aiVector3DVector GetmVertices() {
    IntPtr cPtr = AssimpPINVOKE.aiMesh_GetmVertices(swigCPtr);
    aiVector3DVector ret = (cPtr == IntPtr.Zero) ? null : new aiVector3DVector(cPtr, true);
    return ret;
  }

}
