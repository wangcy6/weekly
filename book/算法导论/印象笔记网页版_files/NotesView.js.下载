

var _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; };

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','jquery','react','classnames','focus-drawer-LoadingSpinner','focus-NotesView-NotesViewSubheader','focus-NotesView-ScrollWindow','css!focus/NotesView/NotesView'],function (require) {
  

  var $ = require('jquery');
  var React = require('react');
  var classnames = require('classnames');

  var LoadingSpinner = require('focus-drawer-LoadingSpinner');
  var NotesViewSubheader = require('focus-NotesView-NotesViewSubheader');
  var ScrollWindow = require('focus-NotesView-ScrollWindow');

  require('css!focus/NotesView/NotesView');

  function prefixedClass(suffix) {
    return 'focus-NotesView-' + suffix;
  }

  /**
   * Top level component that displays notes in a user's account and allows the user to
   * select the note to edit it's contents or perform other actions on the note such as
   * delete, share, or set a reminder. Also lets the user sort the notes and see an
   * overview of how many notes are in their account, as well as manage reminders.
   */
  var NotesView = React.createClass({
    displayName: 'NotesView',

    propTypes: {
      bannerType: React.PropTypes.number,
      noteInfo: React.PropTypes.objectOf(React.PropTypes.shape({
        allowsDelete: React.PropTypes.bool.isRequired,
        allowsExpunge: React.PropTypes.bool.isRequired,
        allowsReminder: React.PropTypes.bool.isRequired,
        allowsRestore: React.PropTypes.bool.isRequired,
        allowsShare: React.PropTypes.bool.isRequired,
        allowsShortcut: React.PropTypes.bool.isRequired,
        date: React.PropTypes.string.isRequired,
        hasReminder: React.PropTypes.bool.isRequired,
        hasShortcut: React.PropTypes.bool.isRequired,
        inTrash: React.PropTypes.bool.isRequired,
        key: React.PropTypes.string.isRequired,
        presentAvatarUrls: React.PropTypes.arrayOf(React.PropTypes.string).isRequired,
        snippet: React.PropTypes.string,
        thumbnailUrl: React.PropTypes.string,
        title: React.PropTypes.string
      })),
      noteViewOptions: React.PropTypes.shape({
        isShowImages: React.PropTypes.bool.isRequired,
        isShowText: React.PropTypes.bool.isRequired,
        sortOptions: React.PropTypes.arrayOf(React.PropTypes.shape({
          isSelected: React.PropTypes.bool.isRequired,
          label: React.PropTypes.string.isRequired,
          value: React.PropTypes.any.isRequired
        })).isRequired
      }),
      notesListDisplayState: React.PropTypes.string,
      notesPresenter: React.PropTypes.shape({
        addShortcut: React.PropTypes.func.isRequired,
        clearScroll: React.PropTypes.func.isRequired,
        expunge: React.PropTypes.func.isRequired,
        fetch: React.PropTypes.func.isRequired,
        remove: React.PropTypes.func.isRequired,
        removeShortcut: React.PropTypes.func.isRequired,
        restore: React.PropTypes.func.isRequired,
        select: React.PropTypes.func.isRequired,
        sendByWorkChat: React.PropTypes.func.isRequired,
        setListIndex: React.PropTypes.func.isRequired,
        setNotebookHeaderScrolled: React.PropTypes.func.isRequired,
        setSortOrder: React.PropTypes.func.isRequired,
        showReminderSetDialog: React.PropTypes.func.isRequired,
        toggleShowImages: React.PropTypes.func.isRequired,
        toggleShowText: React.PropTypes.func.isRequired
      }),
      numNotesBuffer: React.PropTypes.number,
      reminderViewOptions: React.PropTypes.shape({
        isShowRecentlyCompleted: React.PropTypes.bool.isRequired,
        isShowUpcoming: React.PropTypes.bool.isRequired,
        sortOptions: React.PropTypes.arrayOf(React.PropTypes.shape({
          isSelected: React.PropTypes.bool.isRequired,
          label: React.PropTypes.string.isRequired,
          value: React.PropTypes.any.isRequired
        })).isRequired
      }),
      reminders: React.PropTypes.arrayOf(React.PropTypes.shape({
        formattedReminderTime: React.PropTypes.string,
        guid: React.PropTypes.string.isRequired,
        notebookGuid: React.PropTypes.string.isRequired,
        notebookName: React.PropTypes.string.isRequired,
        reminderDoneTime: React.PropTypes.object, // Date
        reminderOrder: React.PropTypes.number,
        reminderTime: React.PropTypes.object, // Date
        title: React.PropTypes.string.isRequired
      })),
      remindersListCollapsedState: React.PropTypes.object,
      remindersListHeight: React.PropTypes.number,
      remindersPresenter: React.PropTypes.shape({
        createReminder: React.PropTypes.func.isRequired,
        markAsDone: React.PropTypes.func.isRequired,
        markAsUndone: React.PropTypes.func.isRequired,
        reorderReminders: React.PropTypes.func.isRequired,
        selectNote: React.PropTypes.func.isRequired,
        setCollapsedReminder: React.PropTypes.func.isRequired,
        setRemindersListHeight: React.PropTypes.func.isRequired,
        setSortOrder: React.PropTypes.func.isRequired,
        showReminderSetDialog: React.PropTypes.func.isRequired,
        toggleShowRecentlyCompleted: React.PropTypes.func.isRequired,
        toggleShowUpcoming: React.PropTypes.func.isRequired
      }),
      scrollToIndex: React.PropTypes.number,
      searchQuery: React.PropTypes.string,
      selectedNoteGuid: React.PropTypes.string,
      selectedNotebookGuid: React.PropTypes.string,
      selectedTagName: React.PropTypes.string,
      totalNotes: React.PropTypes.number
    },

    getDefaultProps: function getDefaultProps() {
      return {
        noteInfo: {},
        reminders: [],
        remindersListCollapsedState: {}
      };
    },

    componentWillMount: function componentWillMount() {
      this.onResize();
      window.addEventListener('resize', this.onResize);
    },

    componentWillUnmount: function componentWillUnmount() {
      window.removeEventListener('resize', this.onResize);
    },

    onResize: function onResize() {
      this.setState({ windowHeight: $(window).height() });
    },

    render: function render() {
      var classes = classnames(prefixedClass('NotesView'));
      var content;
      if (!this.props.noteInfo || !this.props.reminders || !this.props.remindersPresenter || !this.props.notesPresenter || !this.props.noteViewOptions || !this.props.notesListDisplayState || !this.props.reminderViewOptions || this.props.totalNotes === undefined || this.props.numNotesBuffer === undefined) {
        content = React.createElement(LoadingSpinner, null);
      } else {
        content = React.createElement(
          'div',
          { className: classes },
          React.createElement(NotesViewSubheader, this.props),
          React.createElement(ScrollWindow, _extends({}, this.props, { windowHeight: this.state.windowHeight }))
        );
      }
      return React.createElement(
        'div',
        { className: classes },
        content
      );
    }
  });

  return NotesView;
});