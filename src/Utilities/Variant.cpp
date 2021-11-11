#include "Variant.h"

Variant::~Variant() {}

void Variant::ClearConnections() {}

void Variant::Set(std::string const& var)
{
	assert(m_type == TYPE_UNUSED || m_type == TYPE_STRING);
	m_type = TYPE_STRING;
	m_string = var;
}

void Variant::SetVariant(Variant* pVar) { // Needed this because boost was confused...
	Set(*pVar);
}

void Variant::Set(const Variant& v) {
	// Update our data from another variant object
	switch (v.GetType()) {
	case TYPE_FLOAT:
		Set(v.GetFloat());
		break;
	case TYPE_STRING:
		Set(v.GetString());
		break;
	case TYPE_UINT32:
		Set(v.GetUINT32());
		break;
	case TYPE_INT32:
		Set(v.GetINT32());
		break;
	default:
		assert(!"Add support for this var type?");
		break;
	}
}

Variant& Variant::operator+=(const Variant& rhs) {
	if (GetType() == rhs.GetType()) {
		switch (GetType()) {
		case TYPE_FLOAT:
			Set(GetFloat() + rhs.GetFloat());
			break;
		case TYPE_STRING:
			Set(GetString() + rhs.GetString());
			break;
		case TYPE_UINT32:
			Set(GetUINT32() + rhs.GetUINT32());
			break;
		case TYPE_INT32:
			Set(GetINT32() + rhs.GetINT32());
			break;
		default:
			break;
		}
	}

	return *this;
}

Variant& Variant::operator-=(const Variant& rhs) {
	if (GetType() == rhs.GetType()) {
		switch (GetType()) {
		case TYPE_FLOAT:
			Set(GetFloat() - rhs.GetFloat());
			break;
		case TYPE_UINT32:
			Set(GetUINT32() - rhs.GetUINT32());
			break;
		case TYPE_INT32:
			Set(GetINT32() - rhs.GetINT32());
			break;
		default:
			break;
		}
	}

	return *this;
}

bool Variant::operator==(const Variant& rhs) const {
	if (GetType() != rhs.GetType()) {
		return false;
	}

	switch (GetType()) {
	case TYPE_UNUSED:
		return true;
	case TYPE_FLOAT:
		return GetFloat() == rhs.GetFloat();
	case TYPE_STRING:
		return GetString() == rhs.GetString();
	case TYPE_UINT32:
		return GetUINT32() == rhs.GetUINT32();
	case TYPE_INT32:
		return GetINT32() == rhs.GetINT32();
	default:
		assert(!"No equals operator for this type yet implemented");
		return false;
	}
}

bool Variant::operator!=(const Variant& rhs) const {
	return !operator==(rhs);
}

std::string Variant::Print() {
	switch (GetType()) {
	case TYPE_FLOAT:
		return std::to_string(GetFloat());
		break;
	case TYPE_STRING:
		return GetString();
		break;
	case TYPE_UINT32:
		return std::to_string(GetUINT32());
		break;
	case TYPE_INT32:
		return std::to_string(GetINT32());
		break;
	case TYPE_UNUSED:
		return "Unknown";
		break;
	default:
		assert(!"Add support for this var type?");
		break;
	}

	return "Unknown";
}



//curPos is between 0 (value of A) and 1 (value of B)

void Variant::Interpolate(Variant* pA, Variant* pB, float curPos, eInterpolateType type)
{

//	assert(GetType() == pA->GetType() && GetType() == pB->GetType() && "these should all be of the same type");
//	bool bAsColor = false;
//
//	switch (type)
//	{
//	case INTERPOLATE_LINEAR_AS_COLOR:
//		bAsColor = true;
//		break; //as is
//
//	case INTERPOLATE_SMOOTHSTEP:
//		curPos = SMOOTHSTEP(curPos);
//		break;
//
//	case INTERPOLATE_SMOOTHSTEP_AS_COLOR:
//		curPos = SMOOTHSTEP(curPos);
//		bAsColor = true;
//		break;
//
//	case INTERPOLATE_EASE_TO:
//		curPos = EASE_TO(curPos);
//		break;
//	case INTERPOLATE_EASE_FROM:
//		curPos = EASE_FROM(curPos);
//		break;
//
//	case INTERPOLATE_EASE_TO_QUARTIC:
//		curPos = 1 - (curPos = 1 - curPos) * curPos * curPos * curPos;
//		break;
//	case INTERPOLATE_EASE_FROM_QUARTIC:
//		curPos = curPos * curPos * curPos * curPos;
//		break;
//
//	case INTERPOLATE_BOUNCE_TO:
//		if (curPos < 0.36363636f) {
//			curPos = 7.5625f * curPos * curPos;
//		}
//		else if (curPos < 0.72727273f) {
//			curPos = 7.5625f * (curPos -= 0.54545455f) * curPos + 0.75f;
//		}
//		else if (curPos < 0.90909091f) {
//			curPos = 7.5625f * (curPos -= 0.81818182f) * curPos + 0.9375f;
//		}
//		else {
//			curPos = 7.5625f * (curPos -= 0.95454545f) * curPos + 0.984375f;
//		}
//		break;
//
//	case INTERPOLATE_LINEAR:
//		break; //as is
//
//	default:
//		LogError("Unknown interpolation type");
//		assert(0);
//	}
//
//	switch (pA->GetType())
//	{
//
//	case Variant::TYPE_FLOAT:
//	{
//		Set(pA->GetFloat() + ((pB->GetFloat() - pA->GetFloat()) * curPos));
//	}
//	break;
//
//	case Variant::TYPE_VECTOR2:
//	{
//		Set(pA->GetVector2() + ((pB->GetVector2() - pA->GetVector2()) * curPos));
//	}
//
//	break;
//
//	case Variant::TYPE_UINT32:
//	{
//		if (bAsColor)
//		{
//#ifdef _CONSOLE
//			assert(!"Not supported in console builds");
//			pA->Set(pB->GetUINT32());
//#else
//			Set(ColorCombineMix(pA->GetUINT32(), pB->GetUINT32(), curPos));
//#endif
//		}
//		else
//		{
//			Set(uint32(float(pA->GetUINT32()) + ((float(pB->GetUINT32()) - float(pA->GetUINT32())) * curPos)));
//
//		}
//	}
//
//	break;
//
//	case Variant::TYPE_INT32:
//	{
//		Set(int32(float(pA->GetINT32()) + ((float(pB->GetINT32()) - float(pA->GetINT32())) * curPos)));
//	}
//
//	break;
//	default:
//		LogError("Interpolate: Don't handle this combination yet");
//		assert(0);
//	}
}

bool Variant::Save(FILE* fp, const std::string& varName)
{
	//first, filter out types we can't save, like pointers
	//int dataSizeBytes = 0;

	//if (GetType() == TYPE_STRING)
	//{
	//	dataSizeBytes = (int)m_string.size();
	//}
	//else
	//{
	//	dataSizeBytes = GetSizeOfData(GetType());
	//}

	//if (dataSizeBytes == 0)
	//{
	//	LogMsg("Warning: Not going to save variant %s because it was never actually set a value", varName.c_str());
	//	return true; //can't save this type, but not an error
	//}

	//uint32 varType = GetType();
	//int bytesRead = (int)fwrite(&varType, 1, sizeof(uint32), fp);
	//if (bytesRead == 0) return false;

	////save the variable name
	//SaveToFile(varName, fp);

	//if (GetType() == TYPE_STRING)
	//{
	//	SaveToFile(m_string, fp);
	//}
	//else
	//{
	//	fwrite(m_var, dataSizeBytes, 1, fp);
	//}


	return true;
}

inline Variant operator+(Variant lhs, const Variant& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Variant operator-(Variant lhs, const Variant& rhs)
{
	lhs -= rhs;
	return lhs;
}

int GetSizeOfData(Variant::eType type)
{
	/*switch (type)
	{
	case Variant::TYPE_UNUSED:
	case Variant::TYPE_COMPONENT:
	case Variant::TYPE_ENTITY:
		return 0;
		break;

	case Variant::TYPE_UINT32:
	case Variant::TYPE_INT32:
	case Variant::TYPE_FLOAT:
		return 4;
	case Variant::TYPE_VECTOR2:
		return sizeof(CL_Vec2f);
	case Variant::TYPE_VECTOR3:
		return sizeof(CL_Vec3f);
	case Variant::TYPE_RECT:
		return sizeof(CL_Rectf);

	default:

		assert(!"Uh..");
	}*/

	return 0;
}


uint8_t* VariantList::SerializeToMem(uint32_t* pSizeOut, uint8_t* pDest)
{
	int varsUsed = 0;
	int memNeeded = 0;

	int tempSize;

	for (int i = 0; i < C_MAX_VARIANT_LIST_PARMS; i++)
	{
		if (m_variant[i].GetType() == Variant::TYPE_STRING)
		{
			tempSize = (int)m_variant[i].GetString().size() + 4; //the 4 is for an int showing how long the string will be when writing
		}
		else
		{
			tempSize = GetSizeOfData(m_variant[i].GetType());
		}

		if (tempSize > 0)
		{
			varsUsed++;
			memNeeded += tempSize;
		}

	}

	int totalSize = memNeeded + 1 + (varsUsed * 2);


	if (!pDest)
	{
		pDest = new uint8_t[totalSize]; //1 is to write how many are coming
	}

	//write it


	uint8_t* pCur = pDest;

	pCur[0] = uint8_t(varsUsed);
	pCur++;

	uint8_t type;

	for (int i = 0; i < C_MAX_VARIANT_LIST_PARMS; i++)
	{
		if (m_variant[i].GetType() == Variant::TYPE_STRING)
		{
			type = i;
			memcpy(pCur, &type, 1); pCur += 1; //index

			type = Variant::TYPE_STRING;
			memcpy(pCur, &type, 1); pCur += 1; //type


			uint32_t s = (int)m_variant[i].GetString().size();
			memcpy(pCur, &s, 4); pCur += 4; //length of string
			memcpy(pCur, m_variant[i].GetString().c_str(), s); pCur += s; //actual string data
		}
		else
		{
			tempSize = GetSizeOfData(m_variant[i].GetType());

			if (tempSize > 0)
			{
				type = i;
				memcpy(pCur, &type, 1); pCur += 1; //index

				type = m_variant[i].GetType();
				memcpy(pCur, &type, 1); pCur += 1; //type

				memcpy(pCur, m_variant[i].m_var, tempSize); pCur += tempSize;

			}
		}
	}

	*pSizeOut = totalSize;
	return pDest;
}



bool VariantList::SerializeFromMem(uint8_t* pSrc, int bufferSize, int* pBytesReadOut)
{
	uint8_t* pStartPos = pSrc;
	uint8_t count = pSrc[0]; pSrc++;

	for (int i = 0; i < count; i++)
	{
		uint8_t index = pSrc[0]; pSrc++;
		uint8_t type = pSrc[0]; pSrc++;

		switch (type)
		{

		case Variant::TYPE_STRING:
		{
			uint32_t strLen;
			memcpy(&strLen, pSrc, 4); pSrc += 4;

			std::string v;
			v.resize(strLen);
			memcpy(&v[0], pSrc, strLen); pSrc += strLen;
			m_variant[index].Set(v);

			break;
		}

		case Variant::TYPE_UINT32:
		{
			uint32_t v;
			memcpy(&v, pSrc, sizeof(uint32_t));
			pSrc += sizeof(uint32_t);
			m_variant[index].Set(v);
			break;
		}
		case Variant::TYPE_INT32:
		{
			int32_t v;
			memcpy(&v, pSrc, sizeof(int32_t));
			pSrc += sizeof(int32_t);
			m_variant[index].Set(v);
			break;
		}

		case Variant::TYPE_FLOAT:
		{
			float v;
			memcpy(&v, pSrc, sizeof(float));
			pSrc += sizeof(float);
			m_variant[index].Set(v);
			break;
		}

		default:
			//LogMsg("unknown var type");

			if (pBytesReadOut)
				*pBytesReadOut = 0;
			assert(!"Unknown var type");
			return false;
		}
	}

	if (pBytesReadOut)
		*pBytesReadOut = (int)(pSrc - pStartPos);

	return true; //success
}

void VariantList::GetVariantListStartingAt(VariantList* pOut, int startIndex)
{
	int cur = 0;

	for (int i = startIndex; i < C_MAX_VARIANT_LIST_PARMS; i++)
	{
		pOut->m_variant[cur++] = m_variant[i];
	}
}

std::string VariantList::GetContentsAsDebugString()
{
	std::string s;

	for (int i = 0; i < C_MAX_VARIANT_LIST_PARMS; i++)
	{
		if (m_variant[i].GetType() == Variant::TYPE_UNUSED)
		{
			break;
		}
		else
		{
			if (!s.empty()) s += ", ";
			s += "Parm " + std::to_string(i) + ": " + m_variant[i].Print();
		}
	}

	if (s.empty())
	{
		s = "(None)";
	}
	return s;
}