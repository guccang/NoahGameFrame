// -------------------------------------------------------------------------
//    @FileName         :    NFIRecord.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-03-01
//    @Module           :    NFIRecord
//
// -------------------------------------------------------------------------

#ifndef NFI_RECORD_H
#define NFI_RECORD_H

#include "NFIDataList.h"

struct RECORD_EVENT_DATA
{
	enum RecordOptype
	{
		Add = 0,
		Del,
		Swap,
		Create,
		Update,
		Cleared,
		Sort,
		Cover,

		UNKNOW,
	};
	RECORD_EVENT_DATA()
	{
		nOpType = UNKNOW;
		nRow = 0;
		nCol = 0;
	}

	RecordOptype nOpType;
	int nRow;
	int nCol;
	std::string strRecordName;
};

typedef std::function<int(const NFGUID&, const RECORD_EVENT_DATA&, const NFIDataList::TData&, const NFIDataList::TData&)> RECORD_EVENT_FUNCTOR;
typedef NF_SHARE_PTR<RECORD_EVENT_FUNCTOR> RECORD_EVENT_FUNCTOR_PTR;

class NFIRecord
{
public:
    

    typedef std::vector< NF_SHARE_PTR<NFIDataList::TData> > TRECORDVEC;
    typedef TRECORDVEC::const_iterator TRECORDVECCONSTITER;

    virtual ~NFIRecord() {}

    virtual bool IsUsed(const int nRow) const  = 0;
    virtual bool SetUsed(const int nRow, const int bUse)  = 0;

    virtual int GetCols() const  = 0;
    virtual int GetRows() const  = 0;

    virtual TDATA_TYPE GetColType(const int nCol) const = 0;
    virtual const std::string& GetColTag(const int nCol) const = 0;

    // 添加数据
    virtual int AddRow(const int nRow) = 0;
    virtual int AddRow(const int nRow, const NFIDataList& var) = 0;

    virtual bool SetInt(const int nRow, const int nCol, const NFINT64 value) = 0;
    virtual bool SetFloat(const int nRow, const int nCol, const double value) = 0;
    virtual bool SetString(const int nRow, const int nCol, const std::string& value) = 0;
    virtual bool SetObject(const int nRow, const int nCol, const NFGUID& value) = 0;
	virtual bool SetVector2(const int nRow, const int nCol, const NFVector2& value) = 0;
	virtual bool SetVector3(const int nRow, const int nCol, const NFVector3& value) = 0;

    virtual bool SetInt(const int nRow, const std::string& strColTag, const NFINT64 value) = 0;
    virtual bool SetFloat(const int nRow, const std::string& strColTag, const double value) = 0;
    virtual bool SetString(const int nRow, const std::string& strColTag, const std::string& value) = 0;
    virtual bool SetObject(const int nRow, const std::string& strColTag, const NFGUID& value) = 0;
	virtual bool SetVector2(const int nRow, const std::string& strColTag, const NFVector2& value) = 0;
	virtual bool SetVector3(const int nRow, const std::string& strColTag, const NFVector3& value) = 0;

    // 获得数据
    virtual bool QueryRow(const int nRow, NFIDataList& varList) = 0;
    virtual bool SwapRowInfo(const int nOriginRow, const int nTargetRow) = 0;

    virtual NFINT64 GetInt(const int nRow, const int nCol) const = 0;
    virtual double GetFloat(const int nRow, const int nCol) const = 0;
    virtual const std::string& GetString(const int nRow, const int nCol) const = 0;
    virtual const NFGUID& GetObject(const int nRow, const int nCol) const = 0;
	virtual const NFVector2& GetVector2(const int nRow, const int nCol) const = 0;
	virtual const NFVector3& GetVector3(const int nRow, const int nCol) const = 0;

    virtual NFINT64 GetInt(const int nRow, const std::string& strColTag) const = 0;
    virtual double GetFloat(const int nRow, const std::string& strColTag) const = 0;
    virtual const std::string& GetString(const int nRow, const std::string& strColTag) const = 0;
    virtual const NFGUID& GetObject(const int nRow, const std::string& strColTag) const = 0;
	virtual const NFVector2& GetVector2(const int nRow, const std::string& strColTag) const = 0;
	virtual const NFVector3& GetVector3(const int nRow, const std::string& strColTag) const = 0;

    virtual int FindRowByColValue(const int nCol, const NFIDataList& var, NFIDataList& varResult) = 0;
    virtual int FindInt(const int nCol, const NFINT64 value, NFIDataList& varResult) = 0;
    virtual int FindFloat(const int nCol, const double value, NFIDataList& varResult) = 0;
	virtual int FindString(const int nCol, const std::string& value, NFIDataList& varResult) = 0;
    virtual int FindObject(const int nCol, const NFGUID& value, NFIDataList& varResult) = 0;
	virtual int FindVector2(const int nCol, const NFVector2& value, NFIDataList& varResult) = 0;
	virtual int FindVector3(const int nCol, const NFVector3& value, NFIDataList& varResult) = 0;
    virtual int SortByCol(const int nCol, const bool bOrder, NFIDataList& varResult)
    {
        return 0;
    };

    virtual int FindRowByColValue(const std::string& strColTag, const NFIDataList& var, NFIDataList& varResult) = 0;
    virtual int FindInt(const std::string& strColTag, const NFINT64 value, NFIDataList& varResult) = 0;
    virtual int FindFloat(const std::string& strColTag, const double value, NFIDataList& varResult) = 0;
	virtual int FindString(const std::string& strColTag, const std::string& value, NFIDataList& varResult) = 0;
    virtual int FindObject(const std::string& strColTag, const NFGUID& value, NFIDataList& varResult) = 0;
	virtual int FindVector2(const std::string& strColTag, const NFVector2& value, NFIDataList& varResult) = 0;
	virtual int FindVector3(const std::string& strColTag, const NFVector3& value, NFIDataList& varResult) = 0;
    virtual int SortByTag(const std::string& strColTag, const bool bOrder,  NFIDataList& varResult)
    {
        return 0;
    };

    virtual bool Remove(const int nRow) = 0;
    virtual bool Remove(NFIDataList& varRows) //need to optimize
    {
        for (int i  = 0; i < varRows.GetCount(); ++i)
        {
            Remove((int)varRows.Int(i));
        }

        return true;
    }

    virtual bool Clear() = 0;

    virtual void AddRecordHook(const RECORD_EVENT_FUNCTOR_PTR& cb) = 0;

    virtual const bool GetSave() = 0;
    virtual const bool GetPublic() = 0;
    virtual const bool GetPrivate() = 0;
    virtual const bool GetCache() = 0;
	virtual const bool GetUpload() = 0;
    virtual const std::string& GetName() const = 0;

    virtual const NF_SHARE_PTR<NFIDataList> GetInitData() const = 0;
    virtual const NF_SHARE_PTR<NFIDataList> GetTag() const = 0;

    virtual void SetSave(const bool bSave) = 0;
    virtual void SetCache(const bool bCache) = 0;
	virtual void SetUpload(const bool bUpload) = 0;
    virtual void SetPublic(const bool bPublic) = 0;
    virtual void SetPrivate(const bool bPrivate) = 0;
    virtual void SetName(const std::string& strName) = 0;

    virtual const TRECORDVEC& GetRecordVec() const = 0;
};

#endif
