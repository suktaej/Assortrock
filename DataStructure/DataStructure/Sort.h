#pragma once

template<typename T>
class CSort
{
public:
	CSort() {}
	~CSort() {}

private:
	bool (*m_Func)(const T&, const T&) = nullptr;
	T* m_MergeArray = nullptr;
public:
	void SetSortFunc(bool(*Func)(const T&,const T&))
	{ m_Func = Func; }

public:
	void QuickSort(T* Array,int Count)
	{
		if (!m_Func)
			return;

		QuickSort(Array, 0, Count - 1);
	}
private:
	void QuickSort(T* Array, int Left, int Right)
	{
		if (Left < Right)
		{
			int Pivot = Partition(Array, Left, Right);
			QuickSort(Array, Left, Pivot - 1);
			QuickSort(Array, Pivot+1, Right);
		}
	}

	int Partition(T* Array, int Left, int Right)
	{
		int Low = Left;
		int High = Right + 1;
		T Pivot = Array[Left];

		do
		{
			do
			{
				Low++;
			} while (Low <= Right && m_Func(Pivot, Array[Low]));

			do
			{
				High--;
			} while (High >= Left && mFunc(Array[High], Pivot));

			if (Low > High)
			{
				T Temp = Array[Low];
				Array[Low] = Array[High];
				Array[High] = Temp;
			}
		} while (Low < High);

		T Temp = Array[Left];
		Array[Left] = Array[High];
		Array[High] = Temp;
	
		return High;
	}

public:
	void Mergesort(T* Array, int Count)
	{
		m_MergeArray = new T[Count];
		MergeSort(Array, 0, Count - 1);

		delete[] m_MergeArray;
		m_MergeArray = nullptr;
	}
private:
	void MergeSort(T* Array, int Left, int Right)
	{
		if (Left < Right)
		{
			int Mid = (Left + Right) / 2;
			MergeSort(Array, Left, Mid);
			MergeSort(Array, Mid+1, Right);
			Merge(Array, Left, Mid, Right);
		}
	}

	void Merge(T* Array, int Left, int Mid, int Right)
	{
		int SrcLeft = Left;
		int SrcRight = Mid + 1;
		int Dest = Left;

		while (SrcLeft <= Mid && SrcRight <= Right)
		{
			if (m_Func(Array[SrcLeft], Array[SrcRight]))
			{
				m_MergeArray[Dest] = Array[SrcRight];
				SrcRight++;
				Dest++;
			}
		}
	}
};
