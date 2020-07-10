#pragma once
#include "pch.h"
#include "CheatManager.h"
#include "Offsets.h"

namespace GameRenderer {

	void TransformsCalculation(__int64 pBones, __m128* ResultPosition, __m128* BoneInfo)
	{
		__m128 v5; // xmm2
		__m128 v6; // xmm3
		__m128 v7; // xmm0
		__m128 v8; // xmm4
		__m128 v9; // xmm1

		__m128 v10 = { 0.500f, 0.500f, 0.500f, 0.500f };
		__m128 v11 = { 2.000f, 2.000f, 2.000f, 0.000f };

		__m128 v12 = pcm->rvm<__m128>(pBones);
		__m128 v13 = pcm->rvm<__m128>(pBones + 0x10);

		v5 = v13;

		v6 = _mm_mul_ps(*(__m128*)BoneInfo, v5);
		v6.m128_f32[0] = v6.m128_f32[0]
			+ (float)(_mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0x55)) + _mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0xAA)));
		v7 = _mm_shuffle_ps(v13, v5, 0xFF);
		v8 = _mm_sub_ps(
			_mm_mul_ps(_mm_shuffle_ps(v5, v5, 0xD2), *(__m128*)BoneInfo),
			_mm_mul_ps(_mm_shuffle_ps(*(__m128*)BoneInfo, *(__m128*)BoneInfo, 0xD2), v5));
		v9 = _mm_shuffle_ps(v12, v12, 0x93);
		v9.m128_f32[0] = 0.0;
		*(__m128*)ResultPosition = _mm_add_ps(
			_mm_shuffle_ps(v9, v9, 0x39),
			_mm_mul_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_shuffle_ps(v8, v8, 0xD2), v7),
						_mm_mul_ps(_mm_shuffle_ps(v6, v6, 0), v5)),
					_mm_mul_ps(
						_mm_sub_ps(_mm_mul_ps(v7, v7), (__m128)v10),
						*(__m128*)BoneInfo)),
						(__m128)v11));
	}



	Vector3 GetEntityBone(DWORD_PTR Entity, __int64 BoneID)
	{
		__m128 Output;

		__int64 pBonesChain1 = pcm->rvm<__int64>(Entity + 0x908);
		__int64 pBonesChain2 = pcm->rvm<__int64>(pBonesChain1);
		__int64 pBones = pcm->rvm<__int64>(pBonesChain2 + 0x270);
		__int64 pBonesData = pcm->rvm<__int64>(pBones + 0x58);

		__m128 BoneInfo = pcm->rvm<__m128>((0x20 * BoneID) + pBonesData);

		TransformsCalculation(pBones, &Output, &BoneInfo);

		return Vector3(Output.m128_f32[0], Output.m128_f32[1], Output.m128_f32[2]);
	}


	Vector3 W2S(Vector3 position) {
		uint64_t gameRenderer = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_GAMERENDERER);
		if (!gameRenderer) return Vector3(0, 0, 0);

		uint64_t renderDeref = pcm->rvm<uint64_t>(gameRenderer + 0x68);
		if (!renderDeref) return Vector3(0, 0, 0);

		uint64_t engineLink = pcm->rvm<uint64_t>(renderDeref + OFFSET_GAMERENDERER_ENGINELINK);
		if (!engineLink) return Vector3(0, 0, 0);

		uint64_t engine = pcm->rvm<uint64_t>(engineLink + OFFSET_ENGINELINK_ENGINE);
		if (!engine) return Vector3(0, 0, 0);

		uint64_t camera = pcm->rvm<uint64_t>(engine + OFFSET_ENGINE_CAMERA);
		if (!camera) return Vector3(0, 0, 0);

		Vector3 ViewTranslation = pcm->rvm<Vector3>(camera + OFFSET_CAMERA_VIEWTRANSLATION);
		Vector3 ViewRight = pcm->rvm<Vector3>(camera + OFFSET_CAMERA_VIEWRIGHT);
		Vector3 ViewUp = pcm->rvm<Vector3>(camera + OFFSET_CAMERA_VIEWUP);
		Vector3 ViewForward = pcm->rvm<Vector3>(camera + OFFSET_CAMERA_VIEWFORWARD);

		float FOVX = pcm->rvm<float>(camera + OFFSET_CAMERA_VIEWFOVX);
		float FOVY = pcm->rvm<float>(camera + OFFSET_CAMERA_VIEWFOVY);

		Vector3 temp = position - ViewTranslation;

		float x = temp.Dot(ViewRight);
		float y = temp.Dot(ViewUp);
		float z = temp.Dot(ViewForward * -1);

		return Vector3((GetSystemMetrics(SM_CXSCREEN) / 2) * (1 + x / FOVX / z), (GetSystemMetrics(SM_CYSCREEN) / 2) * (1 - y / FOVY / z), z);
	}
	Vector3 GetTranslation() {
		uint64_t gameRenderer = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_GAMERENDERER);
		if (!gameRenderer) return Vector3(0, 0, 0);
		uint64_t renderDeref = pcm->rvm<uint64_t>(gameRenderer + 0x68);
		if (!renderDeref) return Vector3(0, 0, 0);
		uint64_t engineLink = pcm->rvm<uint64_t>(renderDeref + OFFSET_GAMERENDERER_ENGINELINK);
		if (!engineLink) return Vector3(0, 0, 0);
		uint64_t engine = pcm->rvm<uint64_t>(engineLink + OFFSET_ENGINELINK_ENGINE);
		if (!engine) return Vector3(0, 0, 0);
		uint64_t camera = pcm->rvm<uint64_t>(engine + OFFSET_ENGINE_CAMERA);
		if (!camera) return Vector3(0, 0, 0);

		return pcm->rvm<Vector3>(camera + OFFSET_CAMERA_VIEWTRANSLATION);
	}
}