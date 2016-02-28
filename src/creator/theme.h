#ifndef TRANCE_CREATOR_THEME_H
#define TRANCE_CREATOR_THEME_H

#pragma warning(push, 0)
#include <src/trance.pb.h>
#include <wx/frame.h>
#include <wx/notebook.h>
#include <wx/treelist.h>
#pragma warning(pop)

#include <memory>
#include <unordered_map>
#include <vector>

template<typename T>
class ItemList;

class ThemePage : public wxNotebookPage {
public:
  ThemePage(wxNotebook* parent, trance_pb::Session& session,
            const trance_pb::Theme& complete_theme);
  ~ThemePage();
  void RefreshOurData();
  void RefreshData();
  void RefreshRoot();

private:
  trance_pb::Session& _session;
  const trance_pb::Theme& _complete_theme;
  std::string _item_selected;
  std::unique_ptr<ItemList<trance_pb::Theme>> _item_list;
  std::unordered_map<std::string, wxTreeListItem> _tree_lookup;
  wxTreeListCtrl* _tree;
};

#endif