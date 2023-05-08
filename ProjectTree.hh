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


//! @brief Stores data of a server
//!
//! @param name Name of the server.
//! @param ip IP address of the server.
//! @param port TCP port of the server.
//! @param heartbeat Time interval in seconds between heartbeats of the server.
//! @param timeout Limit time to timeout a server connection.
//! @param reconnections Number of times a connection will retry in case of error.
//! @param description String with a user description fo the server.
//!
struct ServerConfig
{
    std::string name;
    std::string ip;
    unsigned int port;
    unsigned int heartbear;
    unsigned int timeout;
    unsigned int reconnections;
    std::string description;
};

//! @brief UI project Tree
//!
//! ProjectTree references the connection elements and after connecting it will
//! list the cluster elements.
//!
//! The interaction to the cluster resources is primary done by user activation
//! of ProjectTree rows.
//!
//! It is based on Gtk::Treeview with the model being contained internally to
//! the class.
//!
class ProjectTree : public Gtk::Box
{
public:
    //! @brief Class constructor
    //!
    ProjectTree ();

    //! @brief Class destructor
    //!
    ~ProjectTree ();

    //! @brief Add a new server to the project tree
    //!
    //! Method to add a new server to the project tree and allocate new
    //! ServerConnectionPage to the specific.
    //!
    //! @param server_config Server configuration data structure.
    //!
    // void AddNewRow(const std::string& row_name);

private:

    class ProjectCell
    {
    public:
        ProjectCell();

        ProjectCell(Gtk::Box* row_box,
                    std::vector<ProjectCell> childs = {});

        ~ProjectCell();

        Gtk::Box* GetRowBox() const;

        void SetRowBox(Gtk::Box* new_row_box);

        std::vector<ProjectCell> GetChilds() const;

    private:

        Gtk::Box* m_row_box;

        std::vector<ProjectCell> m_childs;
    };

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
                                                 const std::vector<ProjectCell>& childs = {},
                                                 Glib::RefPtr<Gio::ListStore<ProjectModel>> child_store = nullptr);

        Gtk::Box* GetRowBox() const;

        void SetRowBox(Gtk::Box* new_row_box);

        std::vector<ProjectCell> GetChilds() const;

        void AppendChild(const ProjectCell& child);

        Glib::RefPtr<Gio::ListStore<ProjectModel>> GetParentStore() const;

        Glib::RefPtr<Gio::ListStore<ProjectModel>> GetChildStore() const;

        void SetChildStore(Glib::RefPtr<Gio::ListStore<ProjectModel>> child_store);

    protected:
        ProjectModel(Gtk::Box* row_box,
                     Glib::RefPtr<Gio::ListStore<ProjectModel>> parent_store,
                     const std::vector<ProjectCell>& childs = {},
                     Glib::RefPtr<Gio::ListStore<ProjectModel>> child_store = nullptr);

    private:
        Gtk::Box* m_row_box;

        Glib::RefPtr<Gio::ListStore<ProjectModel>> m_parent_store;

        std::vector<ProjectCell> m_childs;

        Glib::RefPtr<Gio::ListStore<ProjectModel>> m_child_store;
    };

    //! @brief Signal handler for click action button
    //!
    void on_action_selection_button_clicked ();

    //! @brief Signal handling for change of project tree selections.
    //!
    void on_treeview_selection_change(guint position, guint n_items);

    //! @brief Handler to handle row activation.
    //!
    //! Handler method called by activation of the treeview.
    //! If activation is on the server, and internal resources, etc.
    //! The column parameter is not used by the method, as so it was added C++-17
    //! attribute [[maybe_unused]], to not perform compilation warning.
    //!
    //! @param path Activated row path
    //! @param column Activated row column
    //!
    void on_treeview_row_activated (guint position);

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
