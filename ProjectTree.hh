#ifndef GUI_PROJECTTREE_HH
#define GUI_PROJECTTREE_HH

// GTKMM headers
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/popovermenu.h>
#include <gtkmm/listview.h>
#include <giomm/liststore.h>
#include <gtkmm/listitem.h>
#include <gtkmm/treelistmodel.h>
#include <gtkmm/singleselection.h>

class ProjectTree : public Gtk::Box
{
public:
    //! @brief Class constructor
    //!
    ProjectTree();

    //! @brief Class destructor
    //!
    ~ProjectTree() override;

private:

    //! @brief Tree view data model.
    //!
    //! The data model contain the fields needed for identify the row objects
    //! in the project treeview.
    //!
    class ProjectModel : public Glib::Object
    {
    public:
        static Glib::RefPtr<ProjectModel> create(Gtk::Box* row_box,
                                                 Glib::RefPtr<Gio::ListStore<ProjectModel>> parent_store,
                                                 Glib::RefPtr<Gio::ListStore<ProjectModel>> child_store = nullptr);

        Gtk::Box* GetRowBox() const;

        void AppendChild(const Glib::RefPtr<ProjectModel>& child);

        Glib::RefPtr<Gio::ListStore<ProjectModel>> GetParentStore() const;

        Glib::RefPtr<Gio::ListStore<ProjectModel>> GetChildStore() const;

        void SetChildStore(Glib::RefPtr<Gio::ListStore<ProjectModel>> child_store);

    protected:
        ProjectModel(Gtk::Box* row_box,
                     Glib::RefPtr<Gio::ListStore<ProjectModel>> parent_store,
                     Glib::RefPtr<Gio::ListStore<ProjectModel>> child_store = nullptr);

    private:
        Gtk::Box* m_row_box;

        Glib::RefPtr<Gio::ListStore<ProjectModel>> m_parent_store;

        Glib::RefPtr<Gio::ListStore<ProjectModel>> m_child_store;
    };

    //! @brief Signal handler for click action button
    //!
    void on_action_selection_button_clicked ();

    //! @brief Treeview for project resources object
    //!
    Gtk::ListView m_tree;

    Glib::RefPtr<Gio::ListModel> m_tree_root;

    Glib::RefPtr<Gio::ListStore<ProjectModel>> m_root_store;

    Glib::RefPtr<Gtk::TreeListModel> m_store;

    Glib::RefPtr<Gtk::SingleSelection> m_selection_model;

    //! @brief Options from selection option button
    //!
    Gtk::Button m_button_action_selection;

    //! @brief Popup menu for action selection.
    //!
    Gtk::PopoverMenu m_actions_popup_menu;

    Glib::RefPtr<Gio::ListModel> create_model(
        const Glib::RefPtr<Glib::ObjectBase>& item = {});

    void on_setup_row(const Glib::RefPtr<Gtk::ListItem>& list_item);

    void on_bind_row(const Glib::RefPtr<Gtk::ListItem>& list_item);

    void AddRow();

    void RemoveRow();

    void Unselect();
};

#endif // GUI_PROJECTTREE_HH
